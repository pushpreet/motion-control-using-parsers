%{
#include <stdio.h>

#include "coord.h"
#include "maze.h"
#include "maze_parser.tab.h"

extern "C" int yylex();

void yyerror(const char *str);

%}

%%

"size"		return SIZE;
"start"		return START;
"end"		return END;
"obstacles"	return OBSTACLES;
[=\(\),]	return (int) yytext[0];
[0-9]+		{yylval.num = atoi(yytext); return NUMBER;}
[ \t\n]		;
.			{ECHO; yyerror("Unexpected Character");}

%%

int yywrap(void)
{
	return 1;
}