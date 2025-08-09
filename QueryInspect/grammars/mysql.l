%{
#include <bits/stdc++.h>
#include "mysql.tab.h"  // Bison header
using namespace std;

int currLine = 1;
int currCol = 1;
int lastTokenLength = 0;

static std::string inputBuffer;
static int inputIndex = 0;

void setInputString(const std::string& input) {
    inputBuffer = input;
    inputIndex = 0;
    currLine = 1;
    currCol = 1;
}

int yylex();
int yywrap()   { return 1; }
// Override input to feed from inputBuffer:
int yyinput() {
    if (inputIndex >= inputBuffer.size()) return 0;
    char ch = inputBuffer[inputIndex++];
    if (ch == '\n') { currLine++; currCol = 1; }
    else currCol++;
    return ch;
}

void yyrestart(FILE*) {}  // No-op for compatibility
// For Bison integration:
#define YY_DECL int yylex(void)
%}

%%

[ \t\r]+              { currCol += yyleng; }                    // skip whitespace
\n                    { currLine++; currCol = 1; }

"--".*                { /* skip MySQL comment to end of line */ }

"SELECT"              { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return SELECT; }
"FROM"                { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return FROM; }
"WHERE"               { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return WHERE; }
"AND"|"OR"            { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return LOGICOP; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return IDENTIFIER; }

[0-9]+                { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return INTVAL; }
\'([^\']*)\'|\"([^\"]*)\" { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return STRINGVAL; }

"="|"<"|">"|"<="|">="|"!="  { yylval.strVal = strdup(yytext); lastTokenLength = yyleng; return COMPOP; }

","                     { lastTokenLength = yyleng; return ','; }
";"                     { lastTokenLength = yyleng; return ';'; }
"("                     { lastTokenLength = yyleng; return '('; }
")"                     { lastTokenLength = yyleng; return ')'; }
"*"                     { lastTokenLength = yyleng; return '*'; }

.                       { lastTokenLength = yyleng; return yytext[0]; }

%%

// EOF Handler
int yywrap(void) { return 1; }
