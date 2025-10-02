#include "../include/SyntaxAnalyzer.h"

// Forward declarations from the Flex/Bison parser
extern int yyparse();
extern void setInputString(const string& input);
extern string getSyntaxError();
extern int getErrorLine();
extern int getErrorColumn();

// Global AST root from Bison grammar
extern std::unique_ptr<SqlProgram> sqlProgram;

// TODO: need to implement this (Task for Abhishek Sharma)
QueryComponents QueryBreakdown(const string& query) {
    return QueryComponents();
}

SyntaxResult SyntaxAnalyzer::analyze(const string& query) {
    setInputString(query);  // Give input to Flex
    int parseResult = yyparse();

    if (parseResult == 0) {
        SyntaxResult result(SyntaxStatus::VALID, QueryBreakdown(query));
        
        // 🔹 Move AST from Bison into result
        if (sqlProgram) {
            result.ast = std::move(sqlProgram);
        }
        
        return result;
    } else {
        string errorMsg = getSyntaxError();
        int line = getErrorLine();
        int col = getErrorColumn();

        if (errorMsg.find("unexpected end of input") != string::npos) {
            return SyntaxResult(SyntaxStatus::INCOMPLETE, QueryComponents(), errorMsg, line, col);
        } else {
            return SyntaxResult(SyntaxStatus::INVALID, QueryComponents(), errorMsg, line, col);
        }
    }
}
