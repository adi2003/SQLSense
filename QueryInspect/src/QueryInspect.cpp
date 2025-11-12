#include "../include/QueryInspect.h"
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// QueryInspect implementation
QueryInspect::QueryInspect() : schemaCache(nullptr), semanticEnabled(false) {}

QueryInspect::~QueryInspect() {
    if (schemaCache) {
        delete schemaCache;
    }
}

SyntaxResult QueryInspect::syntaxAnalyze(const string& query) {
    SyntaxAnalyzer analyzer;
    return analyzer.analyze(query);
}

bool QueryInspect::initializeSemanticAnalysis(const string& user, const string& password,
                                                const string& host, int port) {
    if (schemaCache) {
        delete schemaCache;
    }
    
    schemaCache = new SchemaCache(user, password, host, port);
    
    if (!schemaCache->connect()) {
        delete schemaCache;
        schemaCache = nullptr;
        semanticEnabled = false;
        return false;
    }
    
    cout << "Connected to MySQL for semantic analysis\n";
    cout << "Loading schema cache...\n";
    
    // Enhanced schema loading - load all databases and their schemas
    schemaCache->loadDatabaseList();
    
    // Load detailed schema information for all databases
    // auto databases = schemaCache->getDatabases();
    // for (const auto& db : databases) {
    //     cout << "Loading schema for database: " << db << "\n";
    //     schemaCache->loadDatabaseSchema(db); // This method should exist in SchemaCache
    // }
    
    semanticEnabled = true;
    cout << "Schema cache loaded successfully!\n";
    
    return true;
}

SemanticResult QueryInspect::semanticAnalyze(const QueryComponents& components) {
    if (!semanticEnabled || !schemaCache) {
        SemanticResult result;
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE, "Semantic analysis not available"));
        return result;
    }
    
    SemanticAnalyzer semanticAnalyzer(schemaCache);
    
    // Set the current database context if available
    if (!currentDatabase.empty()) {
        semanticAnalyzer.setCurrentDatabase(currentDatabase);
    }
    
    return semanticAnalyzer.analyze(components);
}

// NEW METHOD: Enhanced semantic analysis using AST
SemanticResult QueryInspect::semanticAnalyzeAST(const Statement* statement) {
    if (!semanticEnabled || !schemaCache) {
        SemanticResult result;
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE, "Semantic analysis not available"));
        return result;
    }
    
    SemanticAnalyzer semanticAnalyzer(schemaCache);
    
    // Set the current database context if available
    if (!currentDatabase.empty()) {
        semanticAnalyzer.setCurrentDatabase(currentDatabase);
    }
    
    return semanticAnalyzer.analyze(statement);
}

// NEW METHOD: Enhanced semantic analysis using complete AST program
SemanticResult QueryInspect::semanticAnalyzeProgram(const SqlProgram* program) {
    if (!semanticEnabled || !schemaCache) {
        SemanticResult result;
        result.addIssue(SemanticIssue(SemanticStatus::UNKNOWN_DATABASE, "Semantic analysis not available"));
        return result;
    }
    
    SemanticAnalyzer semanticAnalyzer(schemaCache);
    
    // Set the current database context if available
    if (!currentDatabase.empty()) {
        semanticAnalyzer.setCurrentDatabase(currentDatabase);
    }
    
    return semanticAnalyzer.analyze(program);
}

CompleteAnalysisResult QueryInspect::analyzeComplete(const string& query) {
    CompleteAnalysisResult result;
    
    // First perform syntax analysis
    result.syntaxResult = syntaxAnalyze(query);
    result.overallValid = (result.syntaxResult.status == SyntaxStatus::VALID);
    
    // If syntax is valid and semantic analysis is enabled, perform semantic analysis
    if (result.overallValid && semanticEnabled) {
        // IMPROVED: Try to use AST-based analysis if available
        if (result.syntaxResult.ast != nullptr) {
            // Use the new AST-based semantic analysis
            result.semanticResult = semanticAnalyzeProgram(result.syntaxResult.ast.get());
        } else if (result.syntaxResult.components.queryType != "") {
            // Fallback to legacy QueryComponents analysis
            result.semanticResult = semanticAnalyze(result.syntaxResult.components);
        } else {
            // Create a semantic result indicating incomplete parsing
            result.semanticResult.addWarning("Semantic analysis skipped - incomplete syntax parsing");
        }
        
        result.overallValid = result.overallValid && result.semanticResult.isValid;
    } else if (semanticEnabled && !result.overallValid) {
        // Add a note that semantic analysis was skipped due to syntax errors
        result.semanticResult.addWarning("Semantic analysis skipped due to syntax errors");
    }
    
    return result;
}

void QueryInspect::setDefaultDatabase(const string& database) {
    currentDatabase = database;
    
    // Validate that the database exists if semantic analysis is enabled
    if (semanticEnabled && schemaCache) {
        if (!schemaCache->databaseExists(database)) {
            cout << "Warning: Database '" << database << "' does not exist or is not accessible\n";
            
            // Show available databases as suggestions
            auto availableDbs = getAvailableDatabases();
            if (!availableDbs.empty()) {
                cout << "Available databases: ";
                for (size_t i = 0; i < availableDbs.size(); ++i) {
                    cout << availableDbs[i];
                    if (i < availableDbs.size() - 1) cout << ", ";
                }
                cout << "\n";
            }
        } else {
            cout << "Default database set to: " << database << "\n";
        }
    }
}

vector<string> QueryInspect::getAvailableDatabases() {
    if (!semanticEnabled || !schemaCache) {
        return vector<string>();
    }
    return schemaCache->getDatabases();
}

// NEW METHOD: Get tables for a specific database
vector<string> QueryInspect::getAvailableTables(const string& database) {
    if (!semanticEnabled || !schemaCache) {
        return vector<string>();
    }
    
    string dbToUse = database.empty() ? currentDatabase : database;
    if (dbToUse.empty()) {
        return vector<string>();
    }
    
    auto dbInfo = schemaCache->getDatabaseInfo(dbToUse);
    if (!dbInfo) {
        return vector<string>();
    }
    
    vector<string> tables;
    for (const auto& [tableName, tableInfo] : dbInfo->tables) {
        tables.push_back(tableName);
    }
    
    return tables;
}

// NEW METHOD: Get columns for a specific table
vector<string> QueryInspect::getAvailableColumns(const string& table, const string& database) {
    if (!semanticEnabled || !schemaCache) {
        return vector<string>();
    }
    
    string dbToUse = database.empty() ? currentDatabase : database;
    if (dbToUse.empty() || table.empty()) {
        return vector<string>();
    }
    
    auto tableInfo = schemaCache->getTableInfo(dbToUse, table);
    if (!tableInfo) {
        return vector<string>();
    }
    
    vector<string> columns;
    for (const auto& [columnName, columnInfo] : tableInfo->columns) {
        columns.push_back(columnName);
    }
    
    return columns;
}

void QueryInspect::refreshSchemaCache() {
    if (semanticEnabled && schemaCache) {
        cout << "Refreshing schema cache...\n";
        
        schemaCache->loadDatabaseList();
        
        // Reload detailed schema information for all databases
        // auto databases = schemaCache->getDatabases();
        // for (const auto& db : databases) {
        //     cout << "Reloading schema for database: " << db << "\n";
        //     schemaCache->loadDatabaseSchema(db);
        // }
        
        cout << "Schema cache refreshed successfully!\n";
    }
}

// NEW METHOD: Validate a specific database/table/column exists
bool QueryInspect::validateDatabaseExists(const string& database) {
    if (!semanticEnabled || !schemaCache) {
        return false;
    }
    return schemaCache->databaseExists(database);
}

bool QueryInspect::validateTableExists(const string& table, const string& database) {
    if (!semanticEnabled || !schemaCache) {
        return false;
    }
    
    string dbToUse = database.empty() ? currentDatabase : database;
    if (dbToUse.empty()) {
        return false;
    }
    
    return schemaCache->tableExists(dbToUse, table);
}

bool QueryInspect::validateColumnExists(const string& column, const string& table, const string& database) {
    if (!semanticEnabled || !schemaCache) {
        return false;
    }
    
    string dbToUse = database.empty() ? currentDatabase : database;
    if (dbToUse.empty() || table.empty()) {
        return false;
    }
    
    return schemaCache->columnExists(dbToUse, table, column);
}

// NEW METHOD: Get detailed analysis with suggestions
CompleteAnalysisResult QueryInspect::analyzeCompleteWithSuggestions(const string& query) {
    CompleteAnalysisResult result = analyzeComplete(query);
    
    // Enhanced error reporting with context-aware suggestions
    if (!result.overallValid && semanticEnabled) {
        for (auto& issue : result.semanticResult.issues) {
            // Add contextual suggestions based on available schema
            if (issue.status == SemanticStatus::UNKNOWN_TABLE && !issue.database.empty()) {
                auto tables = getAvailableTables(issue.database);
                if (!tables.empty()) {
                    // Simple similarity check for suggestions
                    for (const auto& table : tables) {
                        if (table.find(issue.table.substr(0, 3)) != string::npos) {
                            issue.suggestion = "Did you mean '" + table + "'?";
                            break;
                        }
                    }
                }
            } else if (issue.status == SemanticStatus::UNKNOWN_COLUMN && !issue.table.empty()) {
                auto columns = getAvailableColumns(issue.table, issue.database);
                if (!columns.empty()) {
                    // Simple similarity check for suggestions
                    for (const auto& column : columns) {
                        if (column.find(issue.column.substr(0, 3)) != string::npos) {
                            issue.suggestion = "Did you mean '" + column + "'?";
                            break;
                        }
                    }
                }
            }
        }
    }
    
    return result;
}

// NEW METHOD: Get schema information for debugging
void QueryInspect::printSchemaInfo(const string& database) {
    if (!semanticEnabled || !schemaCache) {
        cout << "Semantic analysis not enabled\n";
        return;
    }
    
    string dbToUse = database.empty() ? currentDatabase : database;
    if (dbToUse.empty()) {
        cout << "No database specified\n";
        return;
    }
    
    cout << "Schema information for database: " << dbToUse << "\n";
    cout << string(50, '=') << "\n";
    
    auto tables = getAvailableTables(dbToUse);
    for (const auto& table : tables) {
        cout << "Table: " << table << "\n";
        auto columns = getAvailableColumns(table, dbToUse);
        for (const auto& column : columns) {
            cout << "  - " << column << "\n";
        }
        cout << "\n";
    }
}

bool QueryInspect::isSemanticAnalysisEnabled() const {
    return semanticEnabled;
}

string QueryInspect::getCurrentDatabase() const {
    return currentDatabase;
}