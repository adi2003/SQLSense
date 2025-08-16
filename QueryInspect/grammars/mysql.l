%{
#include "mysql.tab.h"
#include <string>
#include <cstring>

int currLine = 1;
int currCol = 1;

// BUFFER FOR QUERY STRING INPUT
std::string inputBuffer;
size_t inputIndex = 0;

// Make this function globally accessible
void setInputString(const std::string& input) {
    inputBuffer = input;
    inputIndex = 0;
    currLine = 1;
    currCol = 1;
}

// FLEX OVERRIDE - custom input function
#define YY_INPUT(buf,result,max_size) \
    { \
        if (inputIndex >= inputBuffer.size()) { \
            result = YY_NULL; \
        } else { \
            size_t n = std::min((size_t)max_size, inputBuffer.size() - inputIndex); \
            memcpy(buf, inputBuffer.c_str() + inputIndex, n); \
            inputIndex += n; \
            result = n; \
            for (size_t i = 0; i < n; i++) { \
                if (buf[i] == '\n') { currLine++; currCol = 1; } \
                else currCol++; \
            } \
        } \
    }
%}

%option noinput nounput noyywrap

%%

[ \t\r]+               { /* skip whitespace */ }
\n                     { /* skip newlines */ }
"--".*                 { /* skip comments */ }

(?i:SELECT)            { yylval.strVal = strdup(yytext); return SELECT; }
(?i:FROM)              { yylval.strVal = strdup(yytext); return FROM; }
(?i:WHERE)             { yylval.strVal = strdup(yytext); return WHERE; }
(?i:AS)                { return AS; }
(?i:AND)|(?i:OR)       { yylval.strVal = strdup(yytext); return LOGICOP; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.strVal = strdup(yytext); return IDENTIFIER; }
\"[^\"]+\"             { yylval.strVal = strdup(yytext); return IDENTIFIER; }
\`[^\`]+`              { yylval.strVal = strdup(yytext); return IDENTIFIER; }

[0-9]+                 { yylval.strVal = strdup(yytext); return INTVAL; }
\'([^\']*)\'           { yylval.strVal = strdup(yytext); return STRINGVAL; }

"="|"<"|">"|"<="|">="|"!=" { yylval.strVal = strdup(yytext); return COMPOP; }
","                    { return ','; }
";"                    { return ';'; }
"("                    { return '('; }
")"                    { return ')'; }
"*"                    { return '*'; }
.                      { return yytext[0]; }

%%
