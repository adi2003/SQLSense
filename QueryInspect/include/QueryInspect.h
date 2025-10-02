#ifndef QUERY_INSPECT_H
#define QUERY_INSPECT_H

#include "SyntaxAnalyzer.h"
#include "SemanticAnalyzer.h"
#include <bits/stdc++.h>
#include "SchemaCache.h"
#include "AST.h"  // Include AST definitions
using namespace std;

// Overall result to mark query Valid or Invalid
struct CompleteAnalysisResult {
    SyntaxResult syntaxResult;
    SemanticResult semanticResult;
    bool overallValid;
    
    CompleteAnalysisResult() : overallValid(false) {}
};

class QueryInspect {
private:
    SchemaCache* schemaCache;
    bool semanticEnabled;
    string currentDatabase;

public:
    QueryInspect();
    ~QueryInspect();
    
    // Syntax Analysis
    SyntaxResult syntaxAnalyze(const string& query);
    
    // Initialize the Semantic analysis
    bool initializeSemanticAnalysis(const string& user = "schema_reader", const string& password = "schema_password",
                                    const string& host = "127.0.0.1", int port = 3306);
    
    // Semantic Analysis Methods
    SemanticResult semanticAnalyze(const QueryComponents& components);           // Legacy method
    SemanticResult semanticAnalyzeAST(const Statement* statement);             // New AST-based method
    SemanticResult semanticAnalyzeProgram(const SqlProgram* program);          // New program-level method
    
    // Complete Analysis
    CompleteAnalysisResult analyzeComplete(const string& query);
    CompleteAnalysisResult analyzeCompleteWithSuggestions(const string& query); // Enhanced with suggestions
    
    // Database context management
    void setDefaultDatabase(const string& database);
    string getCurrentDatabase() const;
    vector<string> getAvailableDatabases();
    vector<string> getAvailableTables(const string& database = "");             // New method
    vector<string> getAvailableColumns(const string& table, const string& database = ""); // New method
    void refreshSchemaCache();
    
    // Schema validation methods
    bool validateDatabaseExists(const string& database);                        // New method
    bool validateTableExists(const string& table, const string& database = ""); // New method
    bool validateColumnExists(const string& column, const string& table, const string& database = ""); // New method
    
    // Debug and utility methods
    void printSchemaInfo(const string& database = "");                         // New method
    
    // Status methods
    bool isSemanticAnalysisEnabled() const;
};

#endif // QUERY_INSPECT_H