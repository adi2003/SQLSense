#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include <bits/stdc++.h>
#include "SemanticAnalyzer.h"
using namespace std;

// Forward declarations from Flex/Bison parser
extern bool parseQueryComponents(const string& query, QueryComponents& components);
extern string getCurrentDatabase();
extern vector<string> getTablesFromQuery();
extern vector<string> getColumnsFromQuery();
extern vector<string> getFunctionsFromQuery();
extern string getQueryType();

class QueryParser {
private:
    string defaultDatabase;
    
    // Helper methods for manual parsing (fallback if Flex/Bison doesn't provide components)
    void parseSelectQuery(const string& query, QueryComponents& components);
    void parseInsertQuery(const string& query, QueryComponents& components);
    void parseUpdateQuery(const string& query, QueryComponents& components);
    void parseDeleteQuery(const string& query, QueryComponents& components);
    
    // Utility methods
    vector<string> extractTableNames(const string& fromClause);
    vector<string> extractColumnNames(const string& selectClause);
    string cleanIdentifier(const string& identifier);
    pair<string, string> splitTableColumn(const string& fullColumn);
    
public:
    QueryParser(const string& defaultDb = "");
    ~QueryParser() = default;
    
    // Main parsing method
    QueryComponents parseQuery(const string& query);
    
    // Configuration
    void setDefaultDatabase(const string& database);
    string getDefaultDatabase() const;
    
    // Query type detection
    string detectQueryType(const string& query);
    bool requiresWritePermission(const string& queryType);
    bool requiresSchemaModification(const string& queryType);
};

#endif // QUERY_PARSER_H