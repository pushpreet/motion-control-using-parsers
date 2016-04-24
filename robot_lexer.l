%option prefix="robot_yy"

%{
#include <stdio.h>

#include "coord.h"
#include "robot_parser.tab.h"

extern "C" int yylex();

void robot_yyerror(const char *str);

int robot_lineno = 1;
%}

%%

"START"		return START;
"END"		return END;
"NODE"		return NODE;
[udlr]  	{robot_yylval.edge = yytext[0]; return EDGE;}
[:\(\),\"]	return (int) yytext[0];
[-]?[0-9]+	{robot_yylval.num = atoi(yytext); return NUMBER;}
\n			{++robot_lineno; return ENDL;}
[ \t]		;
.			{ECHO; robot_yyerror("Unexpected Character");}

%%


void scan_string(const char* str)
{
    yy_scan_string(str);
}

int yywrap(void)
{
	return 1;
}