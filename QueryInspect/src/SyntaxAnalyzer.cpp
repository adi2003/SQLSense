#include "../include/SyntaxAnalyzer.h"

// Forward declarations from the Flex/Bison parser
extern int yyparse();
extern void setInputString(const string& input);
extern string getSyntaxError();
extern int getErrorLine();
extern int getErrorColumn();

SyntaxResult SyntaxAnalyzer::analyze(const string& query) {
    setInputString(query);  // Give input to Flex
    int parseResult = yyparse();

    if (parseResult == 0) {
        return SyntaxResult(SyntaxStatus::VALID);
    } else {
        string errorMsg = getSyntaxError();
        int line = getErrorLine();
        int col = getErrorColumn();

        // You can enhance this logic to detect "incomplete" vs "invalid" based on specific errors
        if (errorMsg.find("unexpected end of input") != string::npos) {
            return SyntaxResult(SyntaxStatus::INCOMPLETE, errorMsg, line, col);
        } else {
            return SyntaxResult(SyntaxStatus::INVALID, errorMsg, line, col);
        }
    }
}
