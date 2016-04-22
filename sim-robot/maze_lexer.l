%option prefix="maze_yy"

%{
#include <stdio.h>

#include "coord.h"
#include "maze_parser.tab.h"

extern "C" int maze_yylex();

void maze_yyerror(const char *str);

int lineno = 1;
%}

%%

"size"		return SIZE;
"start"		return START;
"end"		return END;
"obstacles"	return OBSTACLES;
[=\(\),]	return (int) yytext[0];
[0-9]+		{maze_yylval.num = atoi(yytext); return NUMBER;}
\n			{++lineno;}
[ \t]		;
.			{ECHO; maze_yyerror("Unexpected Character");}

%%

int yywrap(void)
{
	return 1;
}