#include "../include/QueryInspect.h"

SyntaxResult QueryInspect::syntaxAnalyze(const string& query) {
    SyntaxAnalyzer analyzer;
    return analyzer.analyze(query);
}
