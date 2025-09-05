#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <bits/stdc++.h>
#include <SchemaCache.h>
using namespace std;

enum class SyntaxStatus {
    VALID,
    INVALID,
    INCOMPLETE
};

// Query component structures for analysis
struct TableReference {
    string database;
    string table;
    string alias;
    
    TableReference(const string& db = "", const string& tbl = "", const string& als = "")
        : database(db), table(tbl), alias(als) {}
};

struct ColumnReference {
    string database;
    string table;  // Could be table name or alias
    string column;
    string alias;
    
    ColumnReference(const string& db = "", const string& tbl = "", 
                   const string& col = "", const string& als = "")
        : database(db), table(tbl), column(col), alias(als) {}
};

struct FunctionCall {
    string functionName;
    vector<string> arguments;
    DataType expectedReturnType;
    
    FunctionCall(const string& name = "") : functionName(name), expectedReturnType(DataType::UNKNOWN) {}
};

struct QueryComponents {
    string queryType;  // SELECT, INSERT, UPDATE, DELETE, etc.
    string targetDatabase;
    vector<TableReference> tables;
    vector<ColumnReference> columns;
    vector<FunctionCall> functions;
    vector<pair<ColumnReference, string>> whereConditions;  // column, operator
    vector<pair<ColumnReference, string>> assignments;     // for UPDATE/INSERT
    
    QueryComponents() = default;
};

struct SyntaxResult {
    SyntaxStatus status;
    string errorMessage;
    QueryComponents components;
    int errorLine;
    int errorColumn;

    SyntaxResult(SyntaxStatus stat = SyntaxStatus::VALID, QueryComponents comps = QueryComponents(), const string& msg = "", int line = -1, int col = -1)
        : status(stat), components(comps), errorMessage(msg), errorLine(line), errorColumn(col) {}
};

class SyntaxAnalyzer {
public:
    SyntaxResult analyze(const string& query);
};

#endif // SYNTAX_ANALYZER_H
