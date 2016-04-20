%{
#include <stdio.h>
#include "y.tab.h"
%}

%%

size		return SIZE;
start		return START;
end			return END;
obstacles	return OBSTACLES;
[=\(\),]	return (int) yytext[0];
[0-9]+		{yylval = atoi(yytext); return NUMBER;}
[ \t\n]		;
.			{ECHO; yyerror("Unexpected Character");}

%%

int yywrap(void)
{
	return 1;
}