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

bool QueryInspect::initializeSemanticAnalysis(const string& host, int port, 
                                            const string& user, const string& password) {
    if (schemaCache) {
        delete schemaCache;
    }
    
    schemaCache = new SchemaCache();
    
    if (!schemaCache->connect()) {
        delete schemaCache;
        schemaCache = nullptr;
        semanticEnabled = false;
        return false;
    }
    
    cout << "🔗 Connected to MySQL for semantic analysis\n";
    cout << "📚 Loading schema cache...\n";
    
    schemaCache->loadDatabaseList();
    // we need to load other schema components here
    // currently we are only loading the databases.
    semanticEnabled = true;
    
    return true;
}

SemanticResult QueryInspect::semanticAnalyze(const QueryComponents& QueryComponents) {
    SemanticAnalyzer semanticAnalyzer = SemanticAnalyzer(schemaCache);
    return semanticAnalyzer.analyze(QueryComponents);
}

CompleteAnalysisResult QueryInspect::analyzeComplete(const string& query) {
    CompleteAnalysisResult result;
    
    // First perform syntax analysis
    result.syntaxResult = syntaxAnalyze(query);
    result.overallValid = (result.syntaxResult.status == SyntaxStatus::VALID);
    
    QueryComponents QueryComps = result.syntaxResult.components;
    // If syntax is valid and semantic analysis is enabled, perform semantic analysis
    if (result.overallValid && semanticEnabled) {
        result.semanticResult = semanticAnalyze(QueryComps);
        result.overallValid = result.overallValid && result.semanticResult.isValid;
    }
    
    return result;
}

void QueryInspect::setDefaultDatabase(const string& database) {
    currentDatabase = database;
}

vector<string> QueryInspect::getAvailableDatabases() {
    if (!semanticEnabled || !schemaCache) {
        return vector<string>();
    }
    return schemaCache->getDatabases();
}

void QueryInspect::refreshSchemaCache() {
    if (semanticEnabled && schemaCache) {
        schemaCache->loadDatabaseList();
        cout << "✅ Schema cache refreshed\n";
    }
}

bool QueryInspect::isSemanticAnalysisEnabled() const {
    return semanticEnabled;
}