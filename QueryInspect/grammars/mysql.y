%{
#include <bits/stdc++.h>
using namespace std;

extern int currLine;
extern int currCol;
extern int lastTokenLength;

static std::string syntaxError;
static int errorLine = -1;
static int errorColumn = -1;

void yyerror(const char* s);
%}

%union {
    char* strVal;
}

// Declare tokens and precedence
%token <strVal> SELECT FROM WHERE IDENTIFIER INTVAL STRINGVAL LOGICOP COMPOP
%left LOGICOP
%left COMPOP
%token '*'   

%%

entry
    : statement
    ;

statement
    : query ';'      { }
    ;

query
    : SELECT column_list FROM table_ref opt_where { }
    ;

column_list
    : '*'                  { }
    | IDENTIFIER           { }
    | column_list ',' IDENTIFIER { }
    ;

table_ref
    : IDENTIFIER           { }
    ;

opt_where
    : /* empty */          { }
    | WHERE condition      { }
    ;

condition
    : IDENTIFIER COMPOP literal     { }
    | condition LOGICOP condition   { }
    ;

literal
    : INTVAL              { }
    | STRINGVAL           { }
    ;

%%

// Error handler
void yyerror(const char* s) {
    syntaxError = s;
    errorLine = currLine;
    errorColumn = currCol - lastTokenLength;
}

// These provide error reporting for SyntaxAnalyzer
std::string getSyntaxError() { return syntaxError; }
int getErrorLine() { return errorLine; }
int getErrorColumn() { return errorColumn; }

// Needed by some linkers (stub)
int yyparse(void);
