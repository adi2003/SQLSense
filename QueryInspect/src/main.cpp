#include <bits/stdc++.h>
#include "../include/QueryInspect.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Enter a SQL query (terminate with semicolon & enter):\n";
    string sql, line;
    while (getline(cin, line)) {
        sql += line + "\n";
        if (line.find(';') != string::npos) break;
    }

    QueryInspect inspector;
    auto syntaxResult = inspector.syntaxAnalyze(sql);

    if (syntaxResult.status == SyntaxStatus::VALID) {
        cout << "Syntax Valid!\n";
    } else if (syntaxResult.status == SyntaxStatus::INCOMPLETE) {
        cout << "Incomplete statement: " << syntaxResult.errorMessage << endl;
        cout << "At line " << syntaxResult.errorLine << ", column " << syntaxResult.errorColumn << endl;
    } else {
        cout << "Syntax Error: " << syntaxResult.errorMessage << endl;
        cout << "At line " << syntaxResult.errorLine << ", column " << syntaxResult.errorColumn << endl;
    }
    return 0;
}
