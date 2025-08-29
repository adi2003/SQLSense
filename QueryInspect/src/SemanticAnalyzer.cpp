#include "../include/SemanticAnalyzer.h"
#include <algorithm>
#include <regex>

SemanticAnalyzer::SemanticAnalyzer(SchemaCache* cache) : schemaCache(cache) {}

SemanticResult SemanticAnalyzer::analyze(const QueryComponents& components) {
    SemanticResult result;
    
    if (!schemaCache) {
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE, "Schema cache not available"));
        return result;
    }
    
    // Perform various semantic checks
    analyzeTableReferences(components, result);
    analyzeColumnReferences(components, result);
    analyzeTypeCompatibility(components, result);
    analyzeConstraints(components, result);
    analyzePermissions(components, result);
    analyzeFunctions(components, result);
    
    return result;
}

void SemanticAnalyzer::analyzeTableReferences(const QueryComponents& components, SemanticResult& result) {
    for (const auto& tableRef : components.tables) {
        string database = tableRef.database.empty() ? currentDatabase : tableRef.database;
        
        if (database.empty()) {
            result.addWarning("No database context set - table validation skipped");
            continue;
        }
        
        if (!schemaCache->databaseExists(database)) {
            result.addIssue(SemanticIssue(
                SemanticStatus::UNKNOWN_DATABASE,
                "Database '" + database + "' does not exist",
                database
            ));
            continue;
        }
        
        if (!schemaCache->tableExists(database, tableRef.table)) {
            // Try to suggest similar table names
            auto suggestions = suggestSimilarTables(database, tableRef.table);
            string suggestion = suggestions.empty() ? "" : "Did you mean '" + suggestions[0] + "'?";
            
            result.addIssue(SemanticIssue(
                SemanticStatus::UNKNOWN_TABLE,
                "Table '" + tableRef.table + "' does not exist in database '" + database + "'",
                database, tableRef.table, "", -1, -1
            ));
            
            if (!suggestion.empty()) {
                result.issues.back().suggestion = suggestion;
            }
        }
    }
}

void SemanticAnalyzer::analyzeColumnReferences(const QueryComponents& components, SemanticResult& result) {
    for (const auto& colRef : components.columns) {
        string database = colRef.database.empty() ? currentDatabase : colRef.database;
        string table = colRef.table;
        
        // If table is not specified, we need to infer it from the available tables
        if (table.empty() && !components.tables.empty()) {
            // For now, assume the first table if only one table is involved
            if (components.tables.size() == 1) {
                table = components.tables[0].table;
            } else {
                result.addWarning("Ambiguous column reference '" + colRef.column + "' - specify table name");
                continue;
            }
        }
        
        // Resolve table alias to actual table name
        table = resolveTableName(table, components.tables);
        
        if (database.empty() || table.empty()) {
            continue; // Skip if we can't determine context
        }
        
        if (!schemaCache->columnExists(database, table, colRef.column)) {
            auto suggestions = suggestSimilarColumns(database, table, colRef.column);
            string suggestion = suggestions.empty() ? "" : "Did you mean '" + suggestions[0] + "'?";
            
            result.addIssue(SemanticIssue(
                SemanticStatus::UNKNOWN_COLUMN,
                "Column '" + colRef.column + "' does not exist in table '" + table + "'",
                database, table, colRef.column, -1, -1
            ));
            
            if (!suggestion.empty()) {
                result.issues.back().suggestion = suggestion;
            }
        }
    }
}

void SemanticAnalyzer::analyzeTypeCompatibility(const QueryComponents& components, SemanticResult& result) {
    // Check WHERE conditions for type mismatches
    for (const auto& condition : components.whereConditions) {
        const auto& colRef = condition.first;
        const string& operator_ = condition.second;
        
        string database = colRef.database.empty() ? currentDatabase : colRef.database;
        string table = resolveTableName(colRef.table, components.tables);
        
        if (database.empty() || table.empty()) continue;
        
        if (schemaCache->columnExists(database, table, colRef.column)) {
            DataType columnType = schemaCache->getColumnDataType(database, table, colRef.column);
            
            // Check for obvious type mismatches
            if (columnType == DataType::VARCHAR || columnType == DataType::CHAR || columnType == DataType::TEXT) {
                if (operator_ == ">" || operator_ == "<" || operator_ == ">=" || operator_ == "<=") {
                    result.addIssue(SemanticIssue(
                        SemanticStatus::TYPE_MISMATCH,
                        "Type mismatch: using numeric comparison operator '" + operator_ + 
                        "' on text column '" + colRef.column + "'",
                        database, table, colRef.column
                    ));
                    result.issues.back().suggestion = "Use string comparison operators like = or LIKE for text columns";
                }
            }
        }
    }
}

void SemanticAnalyzer::analyzeConstraints(const QueryComponents& components, SemanticResult& result) {
    // Check for NULL constraint violations in assignments (INSERT/UPDATE)
    for (const auto& assignment : components.assignments) {
        const auto& colRef = assignment.first;
        const string& value = assignment.second;
        
        string database = colRef.database.empty() ? currentDatabase : colRef.database;
        string table = resolveTableName(colRef.table, components.tables);
        
        if (database.empty() || table.empty()) continue;
        
        if (schemaCache->columnExists(database, table, colRef.column)) {
            if (!schemaCache->isColumnNullable(database, table, colRef.column)) {
                if (value == "NULL" || value.empty()) {
                    result.addIssue(SemanticIssue(
                        SemanticStatus::NULL_CONSTRAINT_VIOLATION,
                        "Cannot assign NULL to NOT NULL column '" + colRef.column + "'",
                        database, table, colRef.column
                    ));
                    result.issues.back().suggestion = "Provide a valid non-NULL value for this column";
                }
            }
        }
    }
}

void SemanticAnalyzer::analyzePermissions(const QueryComponents& components, SemanticResult& result) {
    // Check for potentially dangerous operations
    string queryType = components.queryType;
    transform(queryType.begin(), queryType.end(), queryType.begin(), ::toupper);
    
    if (queryType == "DROP") {
        result.addIssue(SemanticIssue(
            SemanticStatus::PERMISSION_DENIED,
            "DROP operation detected - potentially destructive and may require special privileges"
        ));
        result.issues.back().suggestion = "Verify you have DROP privileges and backup data before proceeding";
    }
    
    if (queryType == "DELETE" && components.whereConditions.empty()) {
        result.addWarning("DELETE without WHERE clause will remove all rows from the table");
    }
    
    if (queryType == "UPDATE" && components.whereConditions.empty()) {
        result.addWarning("UPDATE without WHERE clause will modify all rows in the table");
    }
}

void SemanticAnalyzer::analyzeFunctions(const QueryComponents& components, SemanticResult& result) {
    for (const auto& funcCall : components.functions) {
        // Check for common MySQL functions
        vector<string> commonFunctions = {
            "COUNT", "SUM", "AVG", "MIN", "MAX", "NOW", "CURDATE", "CURTIME",
            "CONCAT", "SUBSTRING", "LENGTH", "UPPER", "LOWER", "TRIM"
        };
        
        string upperFuncName = funcCall.functionName;
        transform(upperFuncName.begin(), upperFuncName.end(), upperFuncName.begin(), ::toupper);
        
        bool isCommonFunction = find(commonFunctions.begin(), commonFunctions.end(), upperFuncName) != commonFunctions.end();
        
        if (!isCommonFunction) {
            // Check if it exists in the current database
            if (!currentDatabase.empty() && !schemaCache->functionExists(currentDatabase, funcCall.functionName)) {
                result.addIssue(SemanticIssue(
                    SemanticStatus::UNKNOWN_FUNCTION,
                    "Unknown function '" + funcCall.functionName + "'"
                ));
                result.issues.back().suggestion = "Verify function name spelling or check if it's available in your MySQL version";
            }
        }
    }
}

void SemanticAnalyzer::analyzeJoins(const QueryComponents& components, SemanticResult& result) {
    // Basic JOIN analysis - can be expanded
    if (components.tables.size() > 1) {
        // Multiple tables detected - likely a JOIN
        for (size_t i = 1; i < components.tables.size(); ++i) {
            const auto& table1 = components.tables[0];
            const auto& table2 = components.tables[i];
            
            string db1 = table1.database.empty() ? currentDatabase : table1.database;
            string db2 = table2.database.empty() ? currentDatabase : table2.database;
            
            if (db1.empty() || db2.empty()) continue;
            
            // Check if both tables exist
            if (!schemaCache->tableExists(db1, table1.table) || !schemaCache->tableExists(db2, table2.table)) {
                continue; // Already reported as table not found
            }
            
            // Add a warning if no explicit JOIN conditions are visible
            // (This is a simplified check - a full implementation would analyze the WHERE clause)
            result.addWarning("Multiple tables detected - ensure proper JOIN conditions are specified");
        }
    }
}

string SemanticAnalyzer::resolveTableName(const string& tableName, const vector<TableReference>& tables) {
    // First, check if it's already a table name
    for (const auto& table : tables) {
        if (table.table == tableName) {
            return tableName;
        }
        if (table.alias == tableName) {
            return table.table;
        }
    }
    return tableName; // Return as-is if not found
}

bool SemanticAnalyzer::isValidComparison(DataType leftType, DataType rightType, const string& operator_) {
    if (!schemaCache->areTypesCompatible(leftType, rightType)) {
        return false;
    }
    
    // All operators are valid for compatible types
    return true;
}

vector<string> SemanticAnalyzer::getSimilarNames(const string& name, const vector<string>& candidates) {
    vector<string> similar;
    
    // Simple similarity based on substring matching and length
    for (const auto& candidate : candidates) {
        if (candidate.length() >= name.length() - 2 && candidate.length() <= name.length() + 2) {
            // Check for substring match or similar length
            if (candidate.find(name.substr(0, min(3UL, name.length()))) != string::npos ||
                name.find(candidate.substr(0, min(3UL, candidate.length()))) != string::npos) {
                similar.push_back(candidate);
            }
        }
    }
    
    return similar;
}

DataType SemanticAnalyzer::inferExpressionType(const string& expression, const QueryComponents& components) {
    // Simple type inference - can be expanded
    if (regex_match(expression, regex("\\d+"))) {
        return DataType::INTEGER;
    }
    if (regex_match(expression, regex("\\d+\\.\\d+"))) {
        return DataType::DECIMAL;
    }
    if (expression.front() == '\'' && expression.back() == '\'') {
        return DataType::VARCHAR;
    }
    
    return DataType::UNKNOWN;
}

// Individual validation methods
SemanticResult SemanticAnalyzer::validateDatabaseExists(const string& database) {
    SemanticResult result;
    
    if (!schemaCache->databaseExists(database)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::UNKNOWN_DATABASE,
            "Database '" + database + "' does not exist",
            database
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateTableExists(const string& database, const string& table) {
    SemanticResult result;
    
    if (!schemaCache->tableExists(database, table)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::UNKNOWN_TABLE,
            "Table '" + table + "' does not exist in database '" + database + "'",
            database, table
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateColumnExists(const string& database, const string& table, const string& column) {
    SemanticResult result;
    
    if (!schemaCache->columnExists(database, table, column)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::UNKNOWN_COLUMN,
            "Column '" + column + "' does not exist in table '" + table + "'",
            database, table, column
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateTypeCompatibility(const ColumnReference& col1, const ColumnReference& col2, const string& operator_) {
    SemanticResult result;
    
    string db1 = col1.database.empty() ? currentDatabase : col1.database;
    string db2 = col2.database.empty() ? currentDatabase : col2.database;
    
    if (db1.empty() || db2.empty()) {
        return result; // Can't validate without database context
    }
    
    DataType type1 = schemaCache->getColumnDataType(db1, col1.table, col1.column);
    DataType type2 = schemaCache->getColumnDataType(db2, col2.table, col2.column);
    
    if (!isValidComparison(type1, type2, operator_)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "Type mismatch in comparison: cannot compare " + col1.column + " with " + col2.column
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateNullConstraints(const ColumnReference& column, const string& value) {
    SemanticResult result;
    
    string database = column.database.empty() ? currentDatabase : column.database;
    
    if (database.empty()) {
        return result;
    }
    
    if (!schemaCache->isColumnNullable(database, column.table, column.column)) {
        if (value == "NULL" || value.empty()) {
            result.addIssue(SemanticIssue(
                SemanticStatus::NULL_CONSTRAINT_VIOLATION,
                "Cannot assign NULL to NOT NULL column '" + column.column + "'",
                database, column.table, column.column
            ));
        }
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validatePermissions(const string& operation, const string& database, const string& table) {
    SemanticResult result;
    
    if (!schemaCache->hasPrivilege(operation, database, table)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::PERMISSION_DENIED,
            "Insufficient privileges for " + operation + " operation on " + database + "." + table
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateFunction(const FunctionCall& function) {
    SemanticResult result;
    
    if (!currentDatabase.empty() && !schemaCache->functionExists(currentDatabase, function.functionName)) {
        // Check if it's a built-in function
        vector<string> builtinFunctions = {"COUNT", "SUM", "AVG", "MIN", "MAX", "NOW", "CONCAT"};
        string upperName = function.functionName;
        transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
        
        if (find(builtinFunctions.begin(), builtinFunctions.end(), upperName) == builtinFunctions.end()) {
            result.addIssue(SemanticIssue(
                SemanticStatus::UNKNOWN_FUNCTION,
                "Unknown function '" + function.functionName + "'"
            ));
        }
    }
    
    return result;
}

void SemanticAnalyzer::setCurrentDatabase(const string& database) {
    currentDatabase = database;
}

void SemanticAnalyzer::setSchemaCache(SchemaCache* cache) {
    schemaCache = cache;
}

vector<string> SemanticAnalyzer::suggestSimilarTables(const string& database, const string& tableName) {
    if (!schemaCache) return {};
    
    auto dbInfo = schemaCache->getDatabaseInfo(database);
    if (!dbInfo) return {};
    
    vector<string> tableNames;
    for (const auto& [name, info] : dbInfo->tables) {
        tableNames.push_back(name);
    }
    
    return getSimilarNames(tableName, tableNames);
}

vector<string> SemanticAnalyzer::suggestSimilarColumns(const string& database, const string& table, const string& columnName) {
    if (!schemaCache) return {};
    
    auto tableInfo = schemaCache->getTableInfo(database, table);
    if (!tableInfo) return {};
    
    vector<string> columnNames;
    for (const auto& [name, info] : tableInfo->columns) {
        columnNames.push_back(name);
    }
    
    return getSimilarNames(columnName, columnNames);
}

vector<string> SemanticAnalyzer::suggestSimilarFunctions(const string& functionName) {
    vector<string> commonFunctions = {
        "COUNT", "SUM", "AVG", "MIN", "MAX", "NOW", "CURDATE", "CURTIME",
        "CONCAT", "SUBSTRING", "LENGTH", "UPPER", "LOWER", "TRIM"
    };
    
    return getSimilarNames(functionName, commonFunctions);
}