#ifndef QUERY_INSPECT_H
#define QUERY_INSPECT_H

#include <bits/stdc++.h>
#include "SyntaxAnalyzer.h"
using namespace std;

// Simple semantic issue structure
struct SimpleSemanticIssue {
    string message;
    string suggestion;
    
    SimpleSemanticIssue(const string& msg, const string& sug = "") 
        : message(msg), suggestion(sug) {}
};

// Simple semantic result structure
struct SimpleSemanticResult {
    bool isValid;
    vector<SimpleSemanticIssue> issues;
    vector<string> warnings;
    
    SimpleSemanticResult() : isValid(true) {}
    
    void addIssue(const SimpleSemanticIssue& issue) {
        issues.push_back(issue);
        isValid = false;
    }
    
    void addWarning(const string& warning) {
        warnings.push_back(warning);
    }
};

// Enhanced analysis result - COMPLETE DEFINITION
struct EnhancedAnalysisResult {
    SyntaxResult syntaxResult;
    SimpleSemanticResult semanticResult;
    bool overallValid;
    
    EnhancedAnalysisResult() : overallValid(false) {}
};

// Forward declarations
class SimpleSchemaCache;

class QueryInspect {
private:
    SimpleSchemaCache* schemaCache;
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
    SimpleSemanticResult semanticAnalyze(const string& query);
    EnhancedAnalysisResult analyzeComplete(const string& query);
    
    // Database context management
    void setDefaultDatabase(const string& database);
    vector<string> getAvailableDatabases();
    void refreshSchemaCache();
    
    // Status methods
    bool isSemanticAnalysisEnabled() const;
};

#endif // QUERY_INSPECT_H