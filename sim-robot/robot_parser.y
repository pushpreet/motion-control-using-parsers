%{
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "graph.h"

extern "C" int robot_yylex();
extern "C" int robot_yyparse();
extern int lineno;
extern Graph graph;

void robot_yyerror(const char *str);

std::stack<char> trace;
%}

%union
{
	int num;
	char* edge;
}

%start message
%token START END NODE ENDL
%token <num> NUMBER
%type <edge> EDGES
%name-prefix "robot_yy"
%%

message			: node_type ':' position ',' edge_list ENDL
				;

node_type		: START
				| END
				| NODE
				;

position		: '(' NUMBER ',' NUMBER ')'
				;

edge_list 		: '"' edges '"'
				;

edges			:
				| EDGE
				| edges EDGE
				;

%%

void maze_yyerror(const char *str)
{
	fprintf(stderr,"%s at line: %d\n", str, lineno);
}