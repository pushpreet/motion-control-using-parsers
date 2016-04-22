%option prefix="robot_yy"

%{
#include <stdio.h>

#include "robot_parser.tab.h"

extern "C" int yylex();

void robot_yyerror(const char *str);

int lineno = 1;
%}

%%

"START"		return START;
"END"		return END;
"NODE"		return NODE;
[udlr]  	{robot_yylval.edge = yytext[0]; return EDGE;}
[:\(\),\"]	return (int) yytext[0];
[0-9]+		{robot_yylval.num = atoi(yytext); return NUMBER;}
\n			{++lineno; return ENDL}
[ \t]		;
.			{ECHO; robot_yyerror("Unexpected Character");}

%%

int yywrap(void)
{
	return 1;
}