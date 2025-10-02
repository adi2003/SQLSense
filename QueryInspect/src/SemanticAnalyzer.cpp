#include "../include/SemanticAnalyzer.h"
#include <algorithm>
#include <regex>
#include <iostream>

// Initialize static members for FunctionRegistry
map<string, Functioninfo> FunctionRegistry::functions;
bool FunctionRegistry::initialized = false;

SemanticAnalyzer::SemanticAnalyzer(SchemaCache* cache) : schemaCache(cache) {
    FunctionRegistry::initialize();
}

// =============================================================================
// NEW AST-BASED ANALYSIS METHODS
// =============================================================================

SemanticResult SemanticAnalyzer::analyze(const SqlProgram* program) {
    SemanticResult result;
    context.reset();
    
    if (!program) {
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE, "Invalid program AST"));
        return result;
    }
    
    for (const auto& stmt : program->statements) {
        SemanticResult stmtResult = analyzeStatement(stmt.get());
        result.merge(stmtResult);
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyze(const Statement* statement) {
    context.reset();
    return analyzeStatement(statement);
}

SemanticResult SemanticAnalyzer::analyzeStatement(const Statement* stmt) {
    SemanticResult result;
    
    if (!stmt) {
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE, "Null statement"));
        return result;
    }
    
    switch (stmt->nodeType) {
        case NodeType::SELECT_STMT:
            return analyzeSelectStatement(dynamic_cast<const SelectStmt*>(stmt));
        case NodeType::INSERT_STMT:
            return analyzeInsertStatement(dynamic_cast<const InsertStmt*>(stmt));
        case NodeType::UPDATE_STMT:
            return analyzeUpdateStatement(dynamic_cast<const UpdateStmt*>(stmt));
        case NodeType::DELETE_STMT:
            return analyzeDeleteStatement(dynamic_cast<const DeleteStmt*>(stmt));
        case NodeType::CREATE_TABLE_STMT:
            return analyzeCreateTableStatement(dynamic_cast<const CreateTableStmt*>(stmt));
        case NodeType::CREATE_DATABASE_STMT:
            return analyzeCreateDatabaseStatement(dynamic_cast<const CreateDatabaseStmt*>(stmt));
        case NodeType::CREATE_INDEX_STMT:
            return analyzeCreateIndexStatement(dynamic_cast<const CreateIndexStmt*>(stmt));
        case NodeType::CREATE_VIEW_STMT:
            return analyzeCreateViewStatement(dynamic_cast<const CreateViewStmt*>(stmt));
        case NodeType::DROP_STMT:
            return analyzeDropStatement(dynamic_cast<const DropStmt*>(stmt));
        case NodeType::ALTER_STMT:
            return analyzeAlterStatement(dynamic_cast<const AlterStmt*>(stmt));
        default:
            result.addWarning("Unsupported statement type for semantic analysis");
            break;
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeSelectStatement(const SelectStmt* stmt) {
    SemanticResult result;
    
    if (!stmt) return result;
    
    // Analyze FROM clause first to establish table context
    if (!stmt->fromList.empty()) {
        cout<<" from list is not empty"<<endl;
        SemanticResult fromResult = analyzeFromClause(stmt->fromList);
        result.merge(fromResult);
    }
    
    // Set GROUP BY context if present
    if (!stmt->groupByClause.empty()) {
        context.inGroupByContext = true;
        SemanticResult groupByResult = analyzeGroupByClause(stmt->groupByClause);
        result.merge(groupByResult);
    }
    
    // Analyze SELECT list
    if (!stmt->selectList.empty()) {
        cout<<" select list is not empty"<<endl;
        SemanticResult selectResult = analyzeSelectList(stmt->selectList);
        cout<<(selectResult.isValid ? "select result is valid": "select result is invalid")<<endl;
        result.merge(selectResult);
    }
    
    // Analyze WHERE clause
    if (stmt->whereClause) {
        SemanticResult whereResult = analyzeWhereClause(stmt->whereClause.get());
        result.merge(whereResult);
    }
    
    // Analyze HAVING clause
    if (stmt->havingClause) {
        SemanticResult havingResult = analyzeHavingClause(stmt->havingClause.get());
        result.merge(havingResult);
    }
    
    // Analyze ORDER BY clause
    // if (!stmt->orderByList.empty()) {
    //     SemanticResult orderByResult = analyzeOrderByClause(stmt->orderByList);
    //     result.merge(orderByResult);
    // }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeFromClause(const vector<unique_ptr<TableRef>>& fromList) {
    SemanticResult result;
    
    for (const auto& tableRef : fromList) {
        SemanticResult tableResult = analyzeTableReference(tableRef.get());
        result.merge(tableResult);
    }
    
    return result;
}

// --- analyzeTableReference --------------------------------------------------
SemanticResult SemanticAnalyzer::analyzeTableReference(const TableRef* tableRef) {
    SemanticResult result;
    if (!tableRef) {
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_TABLE,
                     "Null table reference", /*db*/"", /*table*/"", /*col*/"", /*line*/-1, /*colpos*/-1));
        return result;
    }

    // Decide which database to use for unqualified tables
    if (currentDatabase.empty()) {
        // If no current DB set, we cannot resolve unqualified table names
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE,
                     "No default database set; cannot resolve table '" + tableRef->tableName + "'",
                     /*db*/"", tableRef->tableName, "", tableRef->line, tableRef->column));
        return result;
    }

    // 1) If this TableRef is a subquery (FROM (SELECT ...) AS alias)
    if (tableRef->subquery) {
        // Recursively analyze the subquery statement
        SemanticResult subqRes = analyzeStatement(tableRef->subquery.get());
        if (!subqRes.isValid) {
            // propagate subquery issues
            return subqRes;
        }
    } else {
        // 2) It's a base table reference: check it exists in the current database
        const string dbToUse = currentDatabase;
        const string& tbl = tableRef->tableName;

        if (!schemaCache->tableExists(dbToUse, tbl)) {
            SemanticIssue issue(SemanticStatus::UNKNOWN_TABLE,
                               "Table '" + tbl + "' does not exist in database '" + dbToUse + "'",
                               dbToUse, tbl, "", tableRef->line, tableRef->column);
            result.addIssue(issue);
            return result;
        }

        // Optionally you could pull the table info and add its columns into the analysis context:
        // const TableInfo* tinfo = schemaCache->getTableInfo(dbToUse, tbl);
        // for (const auto& [colName, colInfo] : tinfo->columns) addColumnToContext(tbl + "." + colName, colInfo.dataType);
    }

    // 3) Process any JOINs attached to this TableRef (joins is vector<unique_ptr<ASTNode>>)
    for (const auto& joinNodePtr : tableRef->joins) {
        if (!joinNodePtr) continue;
        // joinNodePtr should be a JoinClause AST node
        if (auto join = dynamic_cast<JoinClause*>(joinNodePtr.get())) {
            SemanticResult jr = analyzeJoinClause(join);
            if (!jr.isValid) return jr;
        } else {
            // Unexpected node type in joins vector: report a warning/issue
            SemanticIssue issue(SemanticStatus::UNKNOWN_TABLE,
                               "Unexpected node in TableRef->joins (not a JoinClause)",
                               currentDatabase, tableRef->tableName, "", tableRef->line, tableRef->column);
            result.addIssue(issue);
            return result;
        }
    }

    return result; // default: valid (isValid==true)
}

// --- analyzeJoinClause -----------------------------------------------------
SemanticResult SemanticAnalyzer::analyzeJoinClause(const JoinClause* join) {
    SemanticResult result;
    if (!join) {
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_TABLE,
                     "Null join clause", /*db*/"", /*table*/"", /*col*/"", /*line*/-1, /*colpos*/-1));
        return result;
    }

    // 1) Validate the joined table (right-hand side)
    if (!join->table) {
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_TABLE,
                     "Join has no right-side table", currentDatabase, "", "", join->line, join->column));
        return result;
    }

    // Reuse analyzeTableReference to validate the joined table/subquery (and its nested joins)
    SemanticResult tableRes = analyzeTableReference(join->table.get());
    if (!tableRes.isValid) return tableRes;

    // 2) Validate ON condition (if present)
    if (join->onCondition) {
        DataType condType = DataType::UNKNOWN;
        SemanticResult condRes = analyzeExpression(join->onCondition.get(), condType);
        if (!condRes.isValid) return condRes;

        // Join condition must be boolean-ish (depending on your type system)
        // Here we require DataType::BOOLEAN (you can expand to allow numeric truthiness if desired)
        if (condType != DataType::BOOLEAN) {
            SemanticIssue issue(SemanticStatus::TYPE_MISMATCH,
                               "Join ON condition does not evaluate to BOOLEAN",
                               currentDatabase, join->table->tableName, "", join->onCondition->line, join->onCondition->column);
            result.addIssue(issue);
            return result;
        }
    }

    // 3) Validate USING (...) if present (usingColumns)
    if (!join->usingColumns.empty()) {
        // For each column in USING, ensure it exists in both sides of the join (left side assumed in context)
        for (const auto& col : join->usingColumns) {
            cout<<"columns are: "<<col<<endl;
            // We need to resolve column existence: left side tables should be present in context,
            // so check column exists in the joined table and also in context (simplified approach).
            const string db = currentDatabase;
            const string& rightTbl = join->table->tableName;

            if (!schemaCache->columnExists(db, rightTbl, col)) {
                SemanticIssue issue(SemanticStatus::UNKNOWN_COLUMN,
                                   "Column '" + col + "' listed in USING(...) does not exist in table '" + rightTbl + "'",
                                   db, rightTbl, col, join->line, join->column);
                result.addIssue(issue);
                return result;
            }

            // NOTE: checking left-side tables requires analysis context (availableTables), which must be populated
            // earlier by analyzing the left table(s). If you have that context, also validate the column exists there.
        }
    }

    return result; // valid
}


SemanticResult SemanticAnalyzer::analyzeSelectList(const vector<unique_ptr<SelectItem>>& selectList) {
    SemanticResult result;
    
    for (const auto& item : selectList) {
        if (item->expression) {
            DataType resultType;
            SemanticResult exprResult = analyzeExpression(item->expression.get(), resultType);
            result.merge(exprResult);
            
            // Check GROUP BY rules if in GROUP BY context
            if (context.inGroupByContext) {
                validateGroupByRules(item->expression.get(), result);
            }
        }
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeExpression(const Expression* expr, DataType& resultType) {
    SemanticResult result;
    resultType = DataType::UNKNOWN;
    
    if (!expr) return result;
    
    switch (expr->nodeType) {
        case NodeType::IDENTIFIER_EXPR:
            return analyzeIdentifierExpression(dynamic_cast<const IdentifierExpr*>(expr), resultType);
        case NodeType::LITERAL_EXPR:
            return analyzeLiteralExpression(dynamic_cast<const LiteralExpr*>(expr), resultType);
        case NodeType::BINARY_OP_EXPR:
            return analyzeBinaryOpExpression(dynamic_cast<const BinaryOpExpr*>(expr), resultType);
        case NodeType::UNARY_OP_EXPR:
            return analyzeUnaryOpExpression(dynamic_cast<const UnaryOpExpr*>(expr), resultType);
        case NodeType::FUNCTION_CALL_EXPR:
            return analyzeFunctionCallExpression(dynamic_cast<const FunctionCallExpr*>(expr), resultType);
        case NodeType::CASE_EXPR:
            return analyzeCaseExpression(dynamic_cast<const CaseExpr*>(expr), resultType);
        default:
            result.addWarning("Unknown expression type encountered");
            break;
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeIdentifierExpression(const IdentifierExpr* expr, DataType& resultType) {
    SemanticResult result;
    
    if (!expr) return result;
    
    string columnName = expr->name;
    cout<<"column name is: "<<columnName<<endl;
    string tableName = expr->table;
    cout<<"table name is: "<<tableName<<endl;
    
    // Resolve column reference
    if (tableName.empty()) {
        // Find which table this column belongs to
        if (context.availableTables.size() == 1) {
            tableName = context.availableTables[0];
        } else {
            validateColumnAmbiguity(columnName, result);
            return result;
        }
    } else {
        // Resolve table alias
        tableName = resolveTableNameFromContext(tableName);
    }
    
    // Validate column existence
    string database = currentDatabase;
    if (!validateColumnExists(tableName, columnName, result)) {
        return result;
    }
    
    // Get column type
    resultType = getColumnDataType(database, tableName, columnName);
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeLiteralExpression(const LiteralExpr* expr, DataType& resultType) {
    SemanticResult result;
    
    if (!expr) return result;
    
    resultType = literalToDataType(expr);
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeBinaryOpExpression(const BinaryOpExpr* expr, DataType& resultType) {
    SemanticResult result;
    
    if (!expr) return result;
    
    DataType leftType, rightType;
    
    // Analyze left operand
    SemanticResult leftResult = analyzeExpression(expr->left.get(), leftType);
    result.merge(leftResult);
    
    // Analyze right operand
    SemanticResult rightResult = analyzeExpression(expr->right.get(), rightType);
    result.merge(rightResult);
    
    // Check type compatibility
    if (!isValidComparison(leftType, rightType, expr->operator_)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "Type mismatch in binary operation: " + expr->operator_
        ));
    }
    
    // Determine result type
    resultType = getBinaryOpResultType(expr->operator_, leftType, rightType);
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeFunctionCallExpression(const FunctionCallExpr* expr, DataType& resultType) {
    SemanticResult result;
    
    if (!expr) return result;
    
    // Check if function exists
    if (!FunctionRegistry::isValidFunction(expr->functionName)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::UNKNOWN_FUNCTION,
            "Unknown function '" + expr->functionName + "'"
        ));
        return result;
    }
    
    const Functioninfo* funcInfo = FunctionRegistry::getFunction(expr->functionName);
    if (!funcInfo) return result;
    
    // Validate parameter count
    int argCount = expr->arguments.size();
    if (argCount < funcInfo->minParams || 
        (funcInfo->maxParams != -1 && argCount > funcInfo->maxParams)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::UNKNOWN_FUNCTION,
            "Function '" + expr->functionName + "' called with incorrect number of arguments"
        ));
    }
    
    // Analyze arguments
    vector<DataType> argTypes;
    for (const auto& arg : expr->arguments) {
        DataType argType;
        SemanticResult argResult = analyzeExpression(arg.get(), argType);
        result.merge(argResult);
        argTypes.push_back(argType);
    }
    
    // Check aggregate function usage
    if (funcInfo->isAggregate) {
        validateAggregateUsage(expr, result);
    }
    
    resultType = funcInfo->returnType;
    
    return result;
}

// =============================================================================
// HELPER METHOD IMPLEMENTATIONS
// =============================================================================

bool SemanticAnalyzer::validateTableExists(const string& tableName, SemanticResult& result, int line, int col) {
    string database = currentDatabase;
    if (database.empty()) {
        result.addWarning("No database context set");
        return false;
    }
    
    if (!schemaCache || !schemaCache->tableExists(database, tableName)) {
        auto suggestions = suggestSimilarTables(database, tableName);
        string suggestion = suggestions.empty() ? "" : "Did you mean '" + suggestions[0] + "'?";
        
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_TABLE,
            "Table '" + tableName + "' does not exist",
            database, tableName, "", line, col
        );
        if (!suggestion.empty()) {
            issue.suggestion = suggestion;
        }
        result.addIssue(issue);
        return false;
    }
    
    return true;
}

bool SemanticAnalyzer::validateColumnExists(const string& tableName, const string& columnName, 
                                          SemanticResult& result, int line, int col) {

    cout<<"table name: "<<tableName<<endl;
    cout<<"column name: "<<columnName<<endl;                                      
    string database = currentDatabase;
    if (database.empty() || !schemaCache) {
        return false;
    }
    
    if (!schemaCache->columnExists(database, tableName, columnName)) {
        auto suggestions = suggestSimilarColumns(database, tableName, columnName);
        string suggestion = suggestions.empty() ? "" : "Did you mean '" + suggestions[0] + "'?";
        
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_COLUMN,
            "Column '" + columnName + "' does not exist in table '" + tableName + "'",
            database, tableName, columnName, line, col
        );
        if (!suggestion.empty()) {
            issue.suggestion = suggestion;
        }
        result.addIssue(issue);
        return false;
    }
    
    return true;
}

void SemanticAnalyzer::validateColumnAmbiguity(const string& columnName, SemanticResult& result, int line, int col) {
    int matchCount = 0;
    string matchingTable;
    
    for (const auto& tableName : context.availableTables) {
        if (isColumnInContext(columnName, tableName)) {
            matchCount++;
            matchingTable = tableName;
        }
    }
    
    if (matchCount > 1) {
        result.addIssue(SemanticIssue(
            SemanticStatus::AMBIGUOUS_COLUMN,
            "Column '" + columnName + "' is ambiguous - specify table name",
            "", "", columnName, line, col
        ));
    }
}

void SemanticAnalyzer::validateGroupByRules(const Expression* expr, SemanticResult& result) {
    // In GROUP BY context, non-aggregate expressions must be in GROUP BY clause
    if (!expr) return;
    
    if (expr->nodeType == NodeType::FUNCTION_CALL_EXPR) {
        const FunctionCallExpr* funcExpr = dynamic_cast<const FunctionCallExpr*>(expr);
        if (funcExpr && FunctionRegistry::isValidFunction(funcExpr->functionName)) {
            const Functioninfo* funcInfo = FunctionRegistry::getFunction(funcExpr->functionName);
            if (funcInfo && funcInfo->isAggregate) {
                return; // Aggregate functions are allowed
            }
        }
    }
    
    // For non-aggregate expressions, check if they're in GROUP BY
    // This is a simplified check - full implementation would need expression comparison
    result.addIssue(SemanticIssue(
        SemanticStatus::INVALID_GROUP_BY,
        "Non-aggregate expression in SELECT list must appear in GROUP BY clause"
    ));
}

void SemanticAnalyzer::validateAggregateUsage(const Expression* expr, SemanticResult& result) {
    if (context.inAggregateContext) {
        result.addIssue(SemanticIssue(
            SemanticStatus::INVALID_AGGREGATION,
            "Nested aggregate functions are not allowed"
        ));
    }
}

DataType SemanticAnalyzer::getColumnDataType(const string& database, const string& table, const string& column) {
    if (!schemaCache) return DataType::UNKNOWN;
    return schemaCache->getColumnDataType(database, table, column);
}

DataType SemanticAnalyzer::literalToDataType(const LiteralExpr* literal) {
    if (!literal) return DataType::UNKNOWN;
    
    switch (literal->literalType) {
        case LiteralExpr::INTEGER: return DataType::INTEGER;
        case LiteralExpr::DECIMAL: return DataType::DECIMAL;
        case LiteralExpr::STRING: return DataType::VARCHAR;
        case LiteralExpr::BOOLEAN: return DataType::BOOLEAN;
        case LiteralExpr::NULL_VAL: return DataType::NULL_TYPE;
        case LiteralExpr::DATE: return DataType::DATE;
        case LiteralExpr::TIME: return DataType::TIME;
        case LiteralExpr::DATETIME: return DataType::DATETIME;
        default: return DataType::UNKNOWN;
    }
}

DataType SemanticAnalyzer::getBinaryOpResultType(const string& op, DataType leftType, DataType rightType) {
    // Comparison operators return boolean
    if (op == "=" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
        return DataType::BOOLEAN;
    }
    
    // Arithmetic operators
    if (op == "+" || op == "-" || op == "*" || op == "/") {
        if (isNumericType(leftType) && isNumericType(rightType)) {
            // Return the "larger" type
            if (leftType == DataType::DECIMAL || rightType == DataType::DECIMAL) {
                return DataType::DECIMAL;
            }
            return DataType::INTEGER;
        }
    }
    
    // String concatenation
    if (op == "||" || op == "CONCAT") {
        return DataType::VARCHAR;
    }
    
    return getCompatibleType(leftType, rightType);
}

// =============================================================================
// FUNCTION REGISTRY IMPLEMENTATION
// =============================================================================

void FunctionRegistry::initialize() {
    if (initialized) return;
    
    initializeBuiltinFunctions();
    initialized = true;
}

void FunctionRegistry::initializeBuiltinFunctions() {
    // Aggregate functions
    functions["COUNT"] = Functioninfo("COUNT", DataType::INTEGER, true, 1, 1);
    functions["SUM"] = Functioninfo("SUM", DataType::DECIMAL, true, 1, 1);
    functions["AVG"] = Functioninfo("AVG", DataType::DECIMAL, true, 1, 1);
    functions["MIN"] = Functioninfo("MIN", DataType::UNKNOWN, true, 1, 1); // Type depends on input
    functions["MAX"] = Functioninfo("MAX", DataType::UNKNOWN, true, 1, 1); // Type depends on input
    
    // String functions
    functions["CONCAT"] = Functioninfo("CONCAT", DataType::VARCHAR, false, 2, -1);
    functions["SUBSTRING"] = Functioninfo("SUBSTRING", DataType::VARCHAR, false, 2, 3);
    functions["LENGTH"] = Functioninfo("LENGTH", DataType::INTEGER, false, 1, 1);
    functions["UPPER"] = Functioninfo("UPPER", DataType::VARCHAR, false, 1, 1);
    functions["LOWER"] = Functioninfo("LOWER", DataType::VARCHAR, false, 1, 1);
    functions["TRIM"] = Functioninfo("TRIM", DataType::VARCHAR, false, 1, 1);
    
    // Date/time functions
    functions["NOW"] = Functioninfo("NOW", DataType::DATETIME, false, 0, 0);
    functions["CURDATE"] = Functioninfo("CURDATE", DataType::DATE, false, 0, 0);
    functions["CURTIME"] = Functioninfo("CURTIME", DataType::TIME, false, 0, 0);
    
    // Math functions
    functions["ABS"] = Functioninfo("ABS", DataType::DECIMAL, false, 1, 1);
    functions["ROUND"] = Functioninfo("ROUND", DataType::DECIMAL, false, 1, 2);
    functions["FLOOR"] = Functioninfo("FLOOR", DataType::INTEGER, false, 1, 1);
    functions["CEIL"] = Functioninfo("CEIL", DataType::INTEGER, false, 1, 1);
}

bool FunctionRegistry::isValidFunction(const string& name) {
    initialize();
    string upperName = name;
    transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
    return functions.find(upperName) != functions.end();
}

const Functioninfo* FunctionRegistry::getFunction(const string& name) {
    initialize();
    string upperName = name;
    transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
    auto it = functions.find(upperName);
    return (it != functions.end()) ? &it->second : nullptr;
}

vector<string> FunctionRegistry::getAllFunctionNames() {
    initialize();
    vector<string> names;
    for (const auto& [name, info] : functions) {
        names.push_back(name);
    }
    return names;
}

void FunctionRegistry::registerFunction(const Functioninfo& func) {
    initialize();
    string upperName = func.name;
    transform(upperName.begin(), upperName.end(), upperName.begin(), ::toupper);
    functions[upperName] = func;
}

// =============================================================================
// CONTEXT MANAGEMENT AND UTILITY METHODS
// =============================================================================

void SemanticAnalyzer::pushTableToContext(const string& tableName, const string& alias) {
    context.availableTables.push_back(tableName);
    
    if (!alias.empty()) {
        context.tableAliases[alias] = tableName;
    }
    
    // Add all columns from this table to context
    if (schemaCache && !currentDatabase.empty()) {
        auto tableInfo = schemaCache->getTableInfo(currentDatabase, tableName);
        if (tableInfo) {
            for (const auto& [columnName, columnInfo] : tableInfo->columns) {
                string qualifiedName = tableName + "." + columnName;
                context.columnTypes[qualifiedName] = columnInfo.dataType;
            }
        }
    }
}

void SemanticAnalyzer::addColumnToContext(const string& qualifiedColumnName, DataType type) {
    context.columnTypes[qualifiedColumnName] = type;
}

bool SemanticAnalyzer::isColumnInContext(const string& columnName, const string& tableName) {
    if (tableName.empty()) {
        // Check if column exists in any available table
        for (const auto& table : context.availableTables) {
            string qualifiedName = table + "." + columnName;
            if (context.columnTypes.find(qualifiedName) != context.columnTypes.end()) {
                return true;
            }
        }
        return false;
    } else {
        string qualifiedName = tableName + "." + columnName;
        return context.columnTypes.find(qualifiedName) != context.columnTypes.end();
    }
}

string SemanticAnalyzer::resolveTableNameFromContext(const string& tableName) {
    auto it = context.tableAliases.find(tableName);
    return (it != context.tableAliases.end()) ? it->second : tableName;
}

void SemanticAnalyzer::resetContext() {
    context.reset();
}

bool SemanticAnalyzer::isNumericType(DataType type) {
    return type == DataType::INTEGER || type == DataType::DECIMAL || 
           type == DataType::FLOAT || type == DataType::DOUBLE;
}

bool SemanticAnalyzer::isStringType(DataType type) {
    return type == DataType::VARCHAR || type == DataType::CHAR || type == DataType::TEXT;
}

bool SemanticAnalyzer::isDateTimeType(DataType type) {
    return type == DataType::DATE || type == DataType::TIME || type == DataType::DATETIME;
}

DataType SemanticAnalyzer::getCompatibleType(DataType type1, DataType type2) {
    if (type1 == type2) return type1;
    
    // Numeric type promotion
    if (isNumericType(type1) && isNumericType(type2)) {
        if (type1 == DataType::DECIMAL || type2 == DataType::DECIMAL) {
            return DataType::DECIMAL;
        }
        return DataType::INTEGER;
    }
    
    return DataType::UNKNOWN;
}

// =============================================================================
// EXISTING LEGACY METHODS (keeping for backward compatibility)
// =============================================================================

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
            auto suggestions = suggestSimilarTables(database, tableRef.table);
            string suggestion = suggestions.empty() ? "" : "Did you mean '" + suggestions[0] + "'?";
            
            SemanticIssue issue(
                SemanticStatus::UNKNOWN_TABLE,
                "Table '" + tableRef.table + "' does not exist in database '" + database + "'",
                database, tableRef.table, "", -1, -1
            );
            if (!suggestion.empty()) {
                issue.suggestion = suggestion;
            }
            result.addIssue(issue);
        }
    }
}

void SemanticAnalyzer::analyzeColumnReferences(const QueryComponents& components, SemanticResult& result) {
    for (const auto& colRef : components.columns) {
        // cout<<"col :"<<col<<endl;
        string database = colRef.database.empty() ? currentDatabase : colRef.database;
        string table = colRef.table;
        
        if (table.empty() && !components.tables.empty()) {
            if (components.tables.size() == 1) {
                table = components.tables[0].table;
            } else {
                result.addWarning("Ambiguous column reference '" + colRef.column + "' - specify table name");
                continue;
            }
        }
        
        table = resolveTableName(table, components.tables);
        
        if (database.empty() || table.empty()) {
            continue;
        }
        
        if (!schemaCache->columnExists(database, table, colRef.column)) {
            auto suggestions = suggestSimilarColumns(database, table, colRef.column);
            string suggestion = suggestions.empty() ? "" : "Did you mean '" + suggestions[0] + "'?";
            
            SemanticIssue issue(
                SemanticStatus::UNKNOWN_COLUMN,
                "Column '" + colRef.column + "' does not exist in table '" + table + "'",
                database, table, colRef.column, -1, -1
            );
            if (!suggestion.empty()) {
                issue.suggestion = suggestion;
            }
            result.addIssue(issue);
        }
    }
}

void SemanticAnalyzer::analyzeTypeCompatibility(const QueryComponents& components, SemanticResult& result) {
    for (const auto& condition : components.whereConditions) {
        const auto& colRef = condition.first;
        const string& operator_ = condition.second;
        
        string database = colRef.database.empty() ? currentDatabase : colRef.database;
        string table = resolveTableName(colRef.table, components.tables);
        
        if (database.empty() || table.empty()) continue;
        
        if (schemaCache->columnExists(database, table, colRef.column)) {
            DataType columnType = schemaCache->getColumnDataType(database, table, colRef.column);
            
            if (isStringType(columnType)) {
                if (operator_ == ">" || operator_ == "<" || operator_ == ">=" || operator_ == "<=") {
                    SemanticIssue issue(
                        SemanticStatus::TYPE_MISMATCH,
                        "Type mismatch: using numeric comparison operator '" + operator_ + 
                        "' on text column '" + colRef.column + "'",
                        database, table, colRef.column
                    );
                    issue.suggestion = "Use string comparison operators like = or LIKE for text columns";
                    result.addIssue(issue);
                }
            }
        }
    }
}

void SemanticAnalyzer::analyzeConstraints(const QueryComponents& components, SemanticResult& result) {
    for (const auto& assignment : components.assignments) {
        const auto& colRef = assignment.first;
        const string& value = assignment.second;
        
        string database = colRef.database.empty() ? currentDatabase : colRef.database;
        string table = resolveTableName(colRef.table, components.tables);
        
        if (database.empty() || table.empty()) continue;
        
        if (schemaCache->columnExists(database, table, colRef.column)) {
            if (!schemaCache->isColumnNullable(database, table, colRef.column)) {
                if (value == "NULL" || value.empty()) {
                    SemanticIssue issue(
                        SemanticStatus::NULL_CONSTRAINT_VIOLATION,
                        "Cannot assign NULL to NOT NULL column '" + colRef.column + "'",
                        database, table, colRef.column
                    );
                    issue.suggestion = "Provide a valid non-NULL value for this column";
                    result.addIssue(issue);
                }
            }
        }
    }
}

void SemanticAnalyzer::analyzePermissions(const QueryComponents& components, SemanticResult& result) {
    string queryType = components.queryType;
    transform(queryType.begin(), queryType.end(), queryType.begin(), ::toupper);
    
    if (queryType == "DROP") {
        SemanticIssue issue(
            SemanticStatus::PERMISSION_DENIED,
            "DROP operation detected - potentially destructive and may require special privileges"
        );
        issue.suggestion = "Verify you have DROP privileges and backup data before proceeding";
        result.addIssue(issue);
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
        if (!FunctionRegistry::isValidFunction(funcCall.functionName)) {
            SemanticIssue issue(
                SemanticStatus::UNKNOWN_FUNCTION,
                "Unknown function '" + funcCall.functionName + "'"
            );
            
            // Try to suggest similar functions
            auto suggestions = suggestSimilarFunctions(funcCall.functionName);
            if (!suggestions.empty()) {
                issue.suggestion = "Did you mean '" + suggestions[0] + "'?";
            }
            
            result.addIssue(issue);
        }
    }
}

void SemanticAnalyzer::analyzeJoins(const QueryComponents& components, SemanticResult& result) {
    if (components.tables.size() > 1) {
        for (size_t i = 1; i < components.tables.size(); ++i) {
            const auto& table1 = components.tables[0];
            const auto& table2 = components.tables[i];
            
            string db1 = table1.database.empty() ? currentDatabase : table1.database;
            string db2 = table2.database.empty() ? currentDatabase : table2.database;
            
            if (db1.empty() || db2.empty()) continue;
            
            if (!schemaCache->tableExists(db1, table1.table) || !schemaCache->tableExists(db2, table2.table)) {
                continue;
            }
            
            result.addWarning("Multiple tables detected - ensure proper JOIN conditions are specified");
        }
    }
}

string SemanticAnalyzer::resolveTableName(const string& tableName, const vector<TableReference>& tables) {
    for (const auto& table : tables) {
        if (table.table == tableName) {
            return tableName;
        }
        if (table.alias == tableName) {
            return table.table;
        }
    }
    return tableName;
}

string SemanticAnalyzer::resolveColumnName(const string& columnName, const string& tableName) {
    if (tableName.empty()) {
        // Try to find the column in available tables
        for (const auto& table : context.availableTables) {
            if (isColumnInContext(columnName, table)) {
                return table + "." + columnName;
            }
        }
    }
    return tableName.empty() ? columnName : tableName + "." + columnName;
}

bool SemanticAnalyzer::isValidComparison(DataType leftType, DataType rightType, const string& operator_) {
    if (leftType == DataType::UNKNOWN || rightType == DataType::UNKNOWN) {
        return true; // Can't validate unknown types
    }
    
    // Same types are always compatible
    if (leftType == rightType) {
        return true;
    }
    
    // Numeric types are compatible with each other
    if (isNumericType(leftType) && isNumericType(rightType)) {
        return true;
    }
    
    // String types are compatible with each other
    if (isStringType(leftType) && isStringType(rightType)) {
        return true;
    }
    
    // Date/time types are compatible with each other
    if (isDateTimeType(leftType) && isDateTimeType(rightType)) {
        return true;
    }
    
    // Null can be compared with anything
    if (leftType == DataType::NULL_TYPE || rightType == DataType::NULL_TYPE) {
        return true;
    }
    
    return false;
}

vector<string> SemanticAnalyzer::getSimilarNames(const string& name, const vector<string>& candidates) {
    vector<string> similar;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    for (const auto& candidate : candidates) {
        string lowerCandidate = candidate;
        transform(lowerCandidate.begin(), lowerCandidate.end(), lowerCandidate.begin(), ::tolower);
        
        // Check for substring match or similar length
        if (abs(static_cast<int>(candidate.length()) - static_cast<int>(name.length())) <= 2) {
            if (lowerCandidate.find(lowerName.substr(0, min(3UL, lowerName.length()))) != string::npos ||
                lowerName.find(lowerCandidate.substr(0, min(3UL, lowerCandidate.length()))) != string::npos) {
                similar.push_back(candidate);
            }
        }
    }
    
    return similar;
}

DataType SemanticAnalyzer::inferExpressionType(const string& expression, const QueryComponents& components) {
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

bool SemanticAnalyzer::isValidCast(DataType fromType, DataType toType) {
    // Allow casting between compatible types
    if (fromType == toType) return true;
    
    // Numeric types can be cast to each other
    if (isNumericType(fromType) && isNumericType(toType)) return true;
    
    // String types can be cast to each other
    if (isStringType(fromType) && isStringType(toType)) return true;
    
    // Date/time types can be cast to each other
    if (isDateTimeType(fromType) && isDateTimeType(toType)) return true;
    
    // Strings can be cast to most other types
    if (isStringType(fromType)) return true;
    
    return false;
}

bool SemanticAnalyzer::isAggregateFunction(const string& functionName) {
    const Functioninfo* funcInfo = FunctionRegistry::getFunction(functionName);
    return funcInfo ? funcInfo->isAggregate : false;
}

void SemanticAnalyzer::addContextualSuggestion(SemanticIssue& issue, const string& type) {
    if (type == "table") {
        if (!currentDatabase.empty()) {
            auto suggestions = suggestSimilarTables(currentDatabase, issue.table);
            if (!suggestions.empty()) {
                issue.suggestion = "Did you mean '" + suggestions[0] + "'?";
            }
        }
    } else if (type == "column") {
        if (!currentDatabase.empty() && !issue.table.empty()) {
            auto suggestions = suggestSimilarColumns(currentDatabase, issue.table, issue.column);
            if (!suggestions.empty()) {
                issue.suggestion = "Did you mean '" + suggestions[0] + "'?";
            }
        }
    } else if (type == "function") {
        auto suggestions = suggestSimilarFunctions(issue.function);
        if (!suggestions.empty()) {
            issue.suggestion = "Did you mean '" + suggestions[0] + "'?";
        }
    }
}

// =============================================================================
// VALIDATION METHODS
// =============================================================================

SemanticResult SemanticAnalyzer::validateDatabaseExists(const string& database) {
    SemanticResult result;
    
    if (!schemaCache || !schemaCache->databaseExists(database)) {
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
    
    if (!schemaCache || !schemaCache->tableExists(database, table)) {
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_TABLE,
            "Table '" + table + "' does not exist in database '" + database + "'",
            database, table
        );
        addContextualSuggestion(issue, "table");
        result.addIssue(issue);
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateColumnExists(const string& database, const string& table, const string& column) {
    SemanticResult result;
    
    if (!schemaCache || !schemaCache->columnExists(database, table, column)) {
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_COLUMN,
            "Column '" + column + "' does not exist in table '" + table + "'",
            database, table, column
        );
        addContextualSuggestion(issue, "column");
        result.addIssue(issue);
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateTypeCompatibility(const ColumnReference& col1, const ColumnReference& col2, const string& operator_) {
    SemanticResult result;
    
    string db1 = col1.database.empty() ? currentDatabase : col1.database;
    string db2 = col2.database.empty() ? currentDatabase : col2.database;
    
    if (db1.empty() || db2.empty() || !schemaCache) {
        return result;
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
    
    if (database.empty() || !schemaCache) {
        return result;
    }
    
    if (!schemaCache->isColumnNullable(database, column.table, column.column)) {
        if (value == "NULL" || value.empty()) {
            SemanticIssue issue(
                SemanticStatus::NULL_CONSTRAINT_VIOLATION,
                "Cannot assign NULL to NOT NULL column '" + column.column + "'",
                database, column.table, column.column
            );
            issue.suggestion = "Provide a valid non-NULL value for this column";
            result.addIssue(issue);
        }
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validatePermissions(const string& operation, const string& database, const string& table) {
    SemanticResult result;
    
    if (!schemaCache || !schemaCache->hasPrivilege(operation, database, table)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::PERMISSION_DENIED,
            "Insufficient privileges for " + operation + " operation on " + database + "." + table
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateFunction(const FunctionCall& function) {
    SemanticResult result;
    
    if (!FunctionRegistry::isValidFunction(function.functionName)) {
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_FUNCTION,
            "Unknown function '" + function.functionName + "'"
        );
        issue.function = function.functionName;
        addContextualSuggestion(issue, "function");
        result.addIssue(issue);
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateFunction(const string& functionName, const vector<DataType>& argTypes, int line, int col) {
    SemanticResult result;
    
    if (!FunctionRegistry::isValidFunction(functionName)) {
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_FUNCTION,
            "Unknown function '" + functionName + "'",
            "", "", "", line, col
        );
        issue.function = functionName;
        addContextualSuggestion(issue, "function");
        result.addIssue(issue);
        return result;
    }
    
    const Functioninfo* funcInfo = FunctionRegistry::getFunction(functionName);
    if (!funcInfo) return result;
    
    // Validate argument count
    int argCount = argTypes.size();
    if (argCount < funcInfo->minParams || 
        (funcInfo->maxParams != -1 && argCount > funcInfo->maxParams)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::UNKNOWN_FUNCTION,
            "Function '" + functionName + "' called with " + to_string(argCount) + 
            " arguments, expected " + to_string(funcInfo->minParams) + 
            (funcInfo->maxParams == -1 ? " or more" : "-" + to_string(funcInfo->maxParams)),
            "", "", "", line, col
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateAssignment(const string& columnName, const Expression* valueExpr, const string& tableName) {
    SemanticResult result;
    
    if (!schemaCache || currentDatabase.empty() || tableName.empty()) {
        return result;
    }
    
    // Check if column exists
    if (!schemaCache->columnExists(currentDatabase, tableName, columnName)) {
        SemanticIssue issue(
            SemanticStatus::UNKNOWN_COLUMN,
            "Column '" + columnName + "' does not exist in table '" + tableName + "'",
            currentDatabase, tableName, columnName
        );
        addContextualSuggestion(issue, "column");
        result.addIssue(issue);
        return result;
    }
    
    // Get column type and check type compatibility
    DataType columnType = schemaCache->getColumnDataType(currentDatabase, tableName, columnName);
    DataType valueType;
    
    SemanticResult exprResult = analyzeExpression(valueExpr, valueType);
    result.merge(exprResult);
    
    if (!isValidCast(valueType, columnType)) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "Cannot assign value of type to column '" + columnName + "'"
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateInsertValues(const string& tableName, const vector<string>& columns, const vector<ExpressionPtr>& values) {
    SemanticResult result;
    
    if (columns.size() != values.size()) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "Number of columns (" + to_string(columns.size()) + 
            ") doesn't match number of values (" + to_string(values.size()) + ")"
        ));
        return result;
    }
    
    for (size_t i = 0; i < columns.size(); ++i) {
        SemanticResult assignResult = validateAssignment(columns[i], values[i].get(), tableName);
        result.merge(assignResult);
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::validateJoinCondition(const Expression* condition) {
    SemanticResult result;
    
    if (!condition) {
        result.addWarning("JOIN without ON condition may produce cartesian product");
        return result;
    }
    
    DataType conditionType;
    SemanticResult condResult = analyzeExpression(condition, conditionType);
    result.merge(condResult);
    
    // JOIN condition should evaluate to boolean
    if (conditionType != DataType::BOOLEAN && conditionType != DataType::UNKNOWN) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "JOIN condition must evaluate to a boolean expression"
        ));
    }
    
    return result;
}

// =============================================================================
// CONFIGURATION AND UTILITY METHODS
// =============================================================================

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
    vector<string> allFunctions = FunctionRegistry::getAllFunctionNames();
    return getSimilarNames(functionName, allFunctions);
}

void SemanticAnalyzer::printContext() const {
    cout << "=== ANALYSIS CONTEXT ===" << endl;
    cout << "Current Database: " << currentDatabase << endl;
    cout << "Available Tables: ";
    for (const auto& table : context.availableTables) {
        cout << table << " ";
    }
    cout << endl;
    
    cout << "Table Aliases: ";
    for (const auto& [alias, table] : context.tableAliases) {
        cout << alias << "->" << table << " ";
    }
    cout << endl;
    
    cout << "In Aggregate Context: " << (context.inAggregateContext ? "Yes" : "No") << endl;
    cout << "In GROUP BY Context: " << (context.inGroupByContext ? "Yes" : "No") << endl;
    cout << "======================" << endl;
}

void SemanticAnalyzer::printAnalysisResult(const SemanticResult& result) const {
    cout << "=== SEMANTIC ANALYSIS RESULT ===" << endl;
    cout << "Valid: " << (result.isValid ? "Yes" : "No") << endl;
    cout << "Issues (" << result.issues.size() << "):" << endl;
    
    for (const auto& issue : result.issues) {
        cout << "  - " << issue.message;
        if (!issue.suggestion.empty()) {
            cout << " (" << issue.suggestion << ")";
        }
        cout << endl;
    }
    
    cout << "Warnings (" << result.warnings.size() << "):" << endl;
    for (const auto& warning : result.warnings) {
        cout << "  - " << warning << endl;
    }
    cout << "===============================" << endl;
}

// =============================================================================
// PLACEHOLDER IMPLEMENTATIONS FOR MISSING AST METHODS
// =============================================================================

SemanticResult SemanticAnalyzer::analyzeInsertStatement(const InsertStmt* stmt) {
    SemanticResult result;
    // TODO: Implement INSERT statement analysis
    result.addWarning("INSERT statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeUpdateStatement(const UpdateStmt* stmt) {
    SemanticResult result;
    // TODO: Implement UPDATE statement analysis
    result.addWarning("UPDATE statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeDeleteStatement(const DeleteStmt* stmt) {
    SemanticResult result;
    // TODO: Implement DELETE statement analysis
    result.addWarning("DELETE statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeCreateTableStatement(const CreateTableStmt* stmt) {
    SemanticResult result;
    // TODO: Implement CREATE TABLE statement analysis
    result.addWarning("CREATE TABLE statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeCreateDatabaseStatement(const CreateDatabaseStmt* stmt) {
    SemanticResult result;
    // TODO: Implement CREATE DATABASE statement analysis
    result.addWarning("CREATE DATABASE statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeCreateIndexStatement(const CreateIndexStmt* stmt) {
    SemanticResult result;
    // TODO: Implement CREATE INDEX statement analysis
    result.addWarning("CREATE INDEX statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeCreateViewStatement(const CreateViewStmt* stmt) {
    SemanticResult result;
    // TODO: Implement CREATE VIEW statement analysis
    result.addWarning("CREATE VIEW statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeDropStatement(const DropStmt* stmt) {
    SemanticResult result;
    // TODO: Implement DROP statement analysis
    result.addWarning("DROP statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeAlterStatement(const AlterStmt* stmt) {
    SemanticResult result;
    // TODO: Implement ALTER statement analysis
    result.addWarning("ALTER statement analysis not yet implemented");
    return result;
}

SemanticResult SemanticAnalyzer::analyzeUnaryOpExpression(const UnaryOpExpr* expr, DataType& resultType) {
    SemanticResult result;
    // TODO: Implement unary operation analysis
    result.addWarning("Unary operation analysis not yet implemented");
    resultType = DataType::UNKNOWN;
    return result;
}

SemanticResult SemanticAnalyzer::analyzeCaseExpression(const CaseExpr* expr, DataType& resultType) {
    SemanticResult result;
    // TODO: Implement CASE expression analysis
    result.addWarning("CASE expression analysis not yet implemented");
    resultType = DataType::UNKNOWN;
    return result;
}

SemanticResult SemanticAnalyzer::analyzeWhereClause(const Expression* whereExpr) {
    SemanticResult result;
    
    if (!whereExpr) return result;
    
    DataType conditionType;
    SemanticResult exprResult = analyzeExpression(whereExpr, conditionType);
    result.merge(exprResult);
    
    // WHERE condition should evaluate to boolean
    if (conditionType != DataType::BOOLEAN && conditionType != DataType::UNKNOWN) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "WHERE condition must evaluate to a boolean expression"
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeGroupByClause(const vector<ExpressionPtr>& groupByList) {
    SemanticResult result;
    
    for (const auto& expr : groupByList) {
        DataType exprType;
        SemanticResult exprResult = analyzeExpression(expr.get(), exprType);
        result.merge(exprResult);
        
        // Add to GROUP BY context
        // TODO: Store actual expression for later validation
        context.groupByColumns.push_back("expr"); // Placeholder
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeHavingClause(const Expression* havingExpr) {
    SemanticResult result;
    
    if (!havingExpr) return result;
    
    DataType conditionType;
    SemanticResult exprResult = analyzeExpression(havingExpr, conditionType);
    result.merge(exprResult);
    
    // HAVING condition should evaluate to boolean
    if (conditionType != DataType::BOOLEAN && conditionType != DataType::UNKNOWN) {
        result.addIssue(SemanticIssue(
            SemanticStatus::TYPE_MISMATCH,
            "HAVING condition must evaluate to a boolean expression"
        ));
    }
    
    return result;
}

SemanticResult SemanticAnalyzer::analyzeOrderByList(const vector<pair<ExpressionPtr, bool>>& orderByList) {
    SemanticResult result;
    
    for (const auto& [expr, isAsc] : orderByList) {
        DataType exprType;
        SemanticResult exprResult = analyzeExpression(expr.get(), exprType);
        result.merge(exprResult);
    }
    
    return result;
}