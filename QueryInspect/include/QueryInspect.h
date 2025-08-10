#ifndef QUERY_INSPECT_H
#define QUERY_INSPECT_H

#include <bits/stdc++.h>
#include "SyntaxAnalyzer.h"
using namespace std;

class QueryInspect {
public:
    QueryInspect() = default;
    SyntaxResult syntaxAnalyze(const string& query);
    // Later: add semanticAnalyze()
};

#endif // QUERY_INSPECT_H
