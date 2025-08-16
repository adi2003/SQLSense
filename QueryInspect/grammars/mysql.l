%{
#include "mysql.tab.h"
#include <string>
#include <cstring>
#include <algorithm>

int currLine = 1;
int currCol = 1;

std::string inputBuffer;
size_t inputIndex = 0;

void setInputString(const std::string& input) {
    inputBuffer = input;
    inputIndex = 0;
    currLine = 1;
    currCol = 1;
}

#define YY_INPUT(buf,result,max_size) \
    { \
        if (inputIndex >= inputBuffer.size()) { \
            result = 0; \
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

%option caseless noinput nounput noyywrap

%%

[ \t\r]+               { /* skip whitespace */ }
\n                     { /* newline tracked in YY_INPUT */ }

"--".*                 { /* skip single-line comments */ }
"/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"  { /* skip block comment */ }

SELECT              { yylval.strVal = strdup(yytext); return SELECT; }
FROM                { yylval.strVal = strdup(yytext); return FROM; }
WHERE               { yylval.strVal = strdup(yytext); return WHERE; }
AND                 { yylval.strVal = strdup(yytext); return AND; }
OR                  { yylval.strVal = strdup(yytext); return OR; }
UPDATE              { yylval.strVal = strdup(yytext); return UPDATE; }
SET                 { yylval.strVal = strdup(yytext); return SET; }
INSERT              { yylval.strVal = strdup(yytext); return INSERT; }
INTO                { yylval.strVal = strdup(yytext); return INTO; }
VALUES              { yylval.strVal = strdup(yytext); return VALUES; }
DELETE              { yylval.strVal = strdup(yytext); return DELETE; }
CREATE              { yylval.strVal = strdup(yytext); return CREATE; }
TABLE               { yylval.strVal = strdup(yytext); return TABLE; }
DROP                { yylval.strVal = strdup(yytext); return DROP; }
ALTER               { yylval.strVal = strdup(yytext); return ALTER; }
ADD                 { yylval.strVal = strdup(yytext); return ADD; }
JOIN                { yylval.strVal = strdup(yytext); return JOIN; }
INNER               { yylval.strVal = strdup(yytext); return INNER; }
LEFT                { yylval.strVal = strdup(yytext); return LEFT; }
RIGHT               { yylval.strVal = strdup(yytext); return RIGHT; }
FULL                { yylval.strVal = strdup(yytext); return FULL; }
OUTER               { yylval.strVal = strdup(yytext); return OUTER; }
ON                  { yylval.strVal = strdup(yytext); return ON; }
GROUP[ \t\r\n]+BY   { yylval.strVal = strdup("GROUP BY"); return GROUPBY; }
ORDER[ \t\r\n]+BY   { yylval.strVal = strdup("ORDER BY"); return ORDERBY; }
ASC                 { yylval.strVal = strdup(yytext); return ASC; }
DESC                { yylval.strVal = strdup(yytext); return DESC; }
DISTINCT            { yylval.strVal = strdup(yytext); return DISTINCT; }
HAVING              { yylval.strVal = strdup(yytext); return HAVING; }
LIMIT               { yylval.strVal = strdup(yytext); return LIMIT; }
OFFSET              { yylval.strVal = strdup(yytext); return OFFSET; }
AS                  { yylval.strVal = strdup(yytext); return AS; }
PRIMARY             { yylval.strVal = strdup(yytext); return PRIMARY; }
KEY                 { yylval.strVal = strdup(yytext); return KEY; }
FOREIGN             { yylval.strVal = strdup(yytext); return FOREIGN; }
REFERENCES          { yylval.strVal = strdup(yytext); return REFERENCES; }
NOT                 { yylval.strVal = strdup(yytext); return NOT; }
NULL                { yylval.strVal = strdup(yytext); return NULLVAL; }
DEFAULT             { yylval.strVal = strdup(yytext); return DEFAULT; }
CHECK               { yylval.strVal = strdup(yytext); return CHECK; }
UNIQUE              { yylval.strVal = strdup(yytext); return UNIQUE; }
MODIFY              { yylval.strVal = strdup(yytext); return MODIFY; }

[a-zA-Z_][a-zA-Z0-9_]*   { yylval.strVal = strdup(yytext); return IDENTIFIER; }
[0-9]+                   { yylval.strVal = strdup(yytext); return INTVAL; }

\'[^\']*\'               { yylval.strVal = strdup(yytext); return STRINGVAL; }
\"[^\"]*\"               { yylval.strVal = strdup(yytext); return STRINGVAL; }

"<="                { yylval.strVal = strdup(yytext); return COMPOP; }
">="                { yylval.strVal = strdup(yytext); return COMPOP; }
"!="                { yylval.strVal = strdup(yytext); return COMPOP; }
"<>"                { yylval.strVal = strdup(yytext); return COMPOP; }
"="                 { yylval.strVal = strdup(yytext); return COMPOP; }
"<"                 { yylval.strVal = strdup(yytext); return COMPOP; }
">"                 { yylval.strVal = strdup(yytext); return COMPOP; }

","                 { return ','; }
";"                 { return ';'; }
"("                 { return '('; }
")"                 { return ')'; }
"*"                 { return '*'; }
"."                 { return '.'; }

.                   { return yytext[0]; }

%%
