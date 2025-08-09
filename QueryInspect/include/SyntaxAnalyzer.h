#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <bits/stdc++.h>
using namespace std;

enum class SyntaxStatus {
    VALID,
    INVALID,
    INCOMPLETE
};

struct SyntaxResult {
    SyntaxStatus status;
    string errorMessage;
    int errorLine;
    int errorColumn;

    SyntaxResult(SyntaxStatus stat = SyntaxStatus::VALID, const string& msg = "", int line = -1, int col = -1)
        : status(stat), errorMessage(msg), errorLine(line), errorColumn(col) {}
};

class SyntaxAnalyzer {
public:
    SyntaxResult analyze(const string& query);
};

#endif // SYNTAX_ANALYZER_H
