#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <bits/stdc++.h>
#include "SchemaCache.h"
#include "SyntaxAnalyzer.h"
using namespace std;

enum class SemanticStatus {
    VALID,
    TYPE_MISMATCH,
    UNKNOWN_DATABASE,
    UNKNOWN_TABLE,
    UNKNOWN_COLUMN,
    PERMISSION_DENIED,
    CONSTRAINT_VIOLATION,
    UNKNOWN_FUNCTION,
    NULL_CONSTRAINT_VIOLATION
};

struct SemanticIssue {
    SemanticStatus status;
    string message;
    string database;
    string table;
    string column;
    string function;
    int line;
    int column_pos;
    string suggestion;
    
    SemanticIssue(SemanticStatus stat, const string& msg, const string& db = "", 
                  const string& tbl = "", const string& col = "", int ln = -1, int cp = -1)
        : status(stat), message(msg), database(db), table(tbl), column(col), 
          line(ln), column_pos(cp) {}
};

struct SemanticResult {
    bool isValid;
    vector<SemanticIssue> issues;
    vector<string> warnings;
    
    SemanticResult() : isValid(true) {}
    
    void addIssue(const SemanticIssue& issue) {
        issues.push_back(issue);
        if (issue.status != SemanticStatus::VALID) {
            isValid = false;
        }
    }
    
    void addWarning(const string& warning) {
        warnings.push_back(warning);
    }
};

class SemanticAnalyzer {
private:
    SchemaCache* schemaCache;  
    string currentDatabase;  
    
    // Analysis methods
    void analyzeTableReferences(const QueryComponents& components, SemanticResult& result);
    void analyzeColumnReferences(const QueryComponents& components, SemanticResult& result);
    void analyzeTypeCompatibility(const QueryComponents& components, SemanticResult& result);
    void analyzeConstraints(const QueryComponents& components, SemanticResult& result);
    void analyzePermissions(const QueryComponents& components, SemanticResult& result);
    void analyzeFunctions(const QueryComponents& components, SemanticResult& result);
    void analyzeJoins(const QueryComponents& components, SemanticResult& result);
    
    // Helper methods
    string resolveTableName(const string& tableName, const vector<TableReference>& tables);
    bool isValidComparison(DataType leftType, DataType rightType, const string& operator_);
    DataType inferExpressionType(const string& expression, const QueryComponents& components);
    vector<string> getSimilarNames(const string& name, const vector<string>& candidates);
    
public:
    SemanticAnalyzer(SchemaCache* cache);
    ~SemanticAnalyzer() = default;
    
    // Main analysis method
    SemanticResult analyze(const QueryComponents& components);
    
    // Individual validation methods
    SemanticResult validateDatabaseExists(const string& database);
    SemanticResult validateTableExists(const string& database, const string& table);
    SemanticResult validateColumnExists(const string& database, const string& table, const string& column);
    SemanticResult validateTypeCompatibility(const ColumnReference& col1, const ColumnReference& col2, const string& operator_);
    SemanticResult validateNullConstraints(const ColumnReference& column, const string& value);
    SemanticResult validatePermissions(const string& operation, const string& database, const string& table);
    SemanticResult validateFunction(const FunctionCall& function);
    
    // Configuration
    void setCurrentDatabase(const string& database);
    void setSchemaCache(SchemaCache* cache);
    
    // Utility methods
    vector<string> suggestSimilarTables(const string& database, const string& tableName);
    vector<string> suggestSimilarColumns(const string& database, const string& table, const string& columnName);
    vector<string> suggestSimilarFunctions(const string& functionName);
};

#endif // SEMANTIC_ANALYZER_H