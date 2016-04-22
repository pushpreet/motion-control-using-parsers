%{
#include <stdio.h>
#include <stdlib.h>
#include "controller.h"
#include "graph.h"

extern "C" int robot_yylex();
extern "C" int robot_yyparse();
extern int robot_lineno;
extern Controller controller;
extern bool reached;

void robot_yyerror(const char *str);
void getNextStep(Coord pos, char* edges);

int edgeIndex = 0;
Coord robot_coord;
char command;
bool reached;
%}

%union
{
	int num;
	char edge;
	char* edges;
	Coord coord;
}

%start message
%token START END NODE ENDL
%token <num> NUMBER
%token <edge> EDGE
%type <edges> edges edge_list
%type <coord> position
%name-prefix "robot_yy"

%%

message			: msg_prefix ':' msg_suffix ENDL
				;

msg_prefix		: START
				| END								{reached = true;}
				| NODE
				;

msg_suffix		: position ',' edge_list			{controller.visitNode($1, $3); getNextStep($1, $3);}
				;

position		: '(' NUMBER ',' NUMBER ')'			{robot_coord.x = $2, robot_coord.y = $4; $$ = robot_coord;}
				;

edge_list 		: '"' edges '"'						{$$ = $2;}
				;

edges			: EDGE								{$$[edgeIndex] = $1; $$[++edgeIndex] = '\0';}
				| edges EDGE						{$$[edgeIndex] = $2; $$[++edgeIndex] = '\0';}
				;

%%

void getNextStep(Coord pos, char* edges)
{
	for (int i = 0; edges[i] != '\0'; i++)
	{
		if (edges[i] == 'u')
			if (!controller.isVisited(pos.x -1, pos.y)) {command = 'u'; break;}

		else if (edges[i] == 'd')
			if (!controller.isVisited(pos.x +1, pos.y)) {command = 'd'; break;}

		else if (edges[i] == 'l')
			if (!controller.isVisited(pos.x, pos.y -1)) {command = 'l'; break;}

		else if (edges[i] == 'r')
			if (!controller.isVisited(pos.x, pos.y +1)) {command = 'r'; break;}
	}
}

void robot_yyerror(const char *str)
{
	fprintf(stderr,"%s at line: %d\n", str, robot_lineno);
}