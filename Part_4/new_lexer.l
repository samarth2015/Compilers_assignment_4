%{
#include "new_parser.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%option noyywrap
%option yylineno

%%

[ \t\n]+                ;
"Accio"                 { return ACCIO; } 
"Lumos"                 { return LUMOS; } 
"begin"                 { return BEGIN_BLK; }
"end"                   { return END_BLK; }

"variable"              { return VARIABLE; } 
"int"                   { return TYPE_INT; } 
"long"                  { return TYPE_LONG; } 
"short"                 { return TYPE_SHORT; } 
"float"                 { return TYPE_FLOAT; } 
"double"                { return TYPE_DOUBLE; } 
"char"                  { return TYPE_CHAR; } 
"void"                  { return TYPE_VOID; } 

"if"                    { return IF; } 
"else"                  { return ELSE; } 
"while"                 { return WHILE; } 
"for"                   { return FOR; }
"func"                  { return FUNC; } 
"call"                  { return CALL; } 
"return"                { return RETURN; }
"break"                 { return BREAK; } 
"continue"              { return CONTINUE; } 

"&&"                    { return AND; } 
"||"                    { return OR; } 
"!"                     { return NOT; } 
"~"                     { return BIT_NOT; } 

"=="                    { return EQ; } 
"!="                    { return NE; } 
"<="                    { return LE; } 
">="                    { return GE; } 
"<"                     { return LT; } 
">"                     { return GT; } 

"+"                     { return PLUS; } 
"-"                     { return MINUS; }
"*"                     { return MULT; } 
"/"                     { return DIV; } 
"%"                     { return MOD; } 
"&"                     { return BIT_AND; }
"|"                     { return BIT_OR; }
"^"                     { return BIT_XOR; } 

"$"                     { return DOLLAR; }
":"                     { return COLON; } 
"="                     { return ASSIGN; }
","                     { return COMMA; } 
"("                     { return LPAREN; } 
")"                     { return RPAREN; } 

[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }
[0-9]+(\.[0-9]+)?       { yylval.str = strdup(yytext); return NUMBER; } 
\"[^\"]*\"              { yylval.str = strdup(yytext); return STRING; } 
\'[^\']\'               { yylval.str = strdup(yytext); return CHAR_LIT; } 

. { fprintf(stderr, "[Lexical Error] Line %d: Unknown character '%s'\n", yylineno, yytext); }

%%