#ifndef QUERY_INSPECT_H
#define QUERY_INSPECT_H

#include <bits/stdc++.h>
#include "SyntaxAnalyzer.h"
#include "SemanticAnalyzer.h"
#include "SchemaCache.h"
using namespace std;

// Enhanced analysis result - COMPLETE DEFINITION
struct CompleteAnalysisResult {
    SyntaxResult syntaxResult;
    SemanticResult semanticResult;
    bool overallValid;
    
    CompleteAnalysisResult() : overallValid(false) {}
};

// Forward declarations
class SchemaCache;

class QueryInspect {
private:
    SchemaCache* schemaCache;
    bool semanticEnabled;
    string currentDatabase;

public:
    QueryInspect();
    ~QueryInspect();
    
    // Original syntax analysis method (maintains compatibility)
    SyntaxResult syntaxAnalyze(const string& query);
    
    // New semantic analysis methods
    bool initializeSemanticAnalysis(const string& host = "127.0.0.1", int port = 3306,
                                  const string& user = "schema_reader", const string& password = "schema_password");
    SemanticResult semanticAnalyze(const QueryComponents& components);
    CompleteAnalysisResult analyzeComplete(const string& query);
    
    // Database context management
    void setDefaultDatabase(const string& database);
    vector<string> getAvailableDatabases();
    void refreshSchemaCache();
    
    // Status methods
    bool isSemanticAnalysisEnabled() const;
};

#endif // QUERY_INSPECT_H