%option yylineno
%option noyywrap

%{
#include <ast/ast.h>
#include "sysy.tab.hh"
#include <stdio.h>
#include <string>
#include <ctype.h>
int line_count = 1;
extern bool error;
%}


int_number 0|[1-9][0-9]*
identifier [a-zA-Z_][a-zA-Z0-9_]*
blank [ \t\n]
NOTE_S     "/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"
NOTE_M     "//".* 

%%

{NOTE_S}* {}
{NOTE_M}* { line_count++; } 
[ ] { }
"\t"    {}
"\r"    {}
"\n"    { line_count++; }

"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"%"     { return MOD; }

"=="    { return L_EQUAL; }
"!="    { return NE; }
"<"     { return LT; }
"<="    { return LE; }
">"     { return GT; }
">="    { return GE; }

"("     { return LP; }
")"     { return RP; }
"["     { return LB; }
"]"     { return RB; }
"{"     { return LC; }
"}"     { return RC; }
","     { return COMMA; }
";"     { return SEMICOLON; }

"!"     { return L_NOT; }
"="     { return ASSIGN; }

"&&"    { return L_AND; }
"||"    { return L_OR; }


"return"    { return RETURN; }
"while"     { return WHILE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"if"        { return IF; }
"else"      { return ELSE; }

"void"      { return VOID; }
"int"       { return INT; }

{identifier} {
    yylval.str_Val = (char *)malloc(strlen(yytext) + 1);
    strcpy(yylval.str_Val, yytext);
    yylval.str_Val[strlen(yytext)] = '\0';
    return ID;
}

{int_number} { 
    yylval.int_Val = atoi(yytext); 
    return INT_CONST; 
}

.        { printf("line:%d ERROR(%s)\n", line_count, yytext); error = true;}
%%
