%{
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "maze.h"

extern "C" int maze_yylex();
extern "C" int maze_yyparse();
extern int maze_lineno;

void maze_yyerror(const char *str);
void maze_yySemanticError(const char* str);

Maze maze;
Coord coord;
std::vector<Coord> obstacles;

char errors[][50] = {"start coordinate out of bounds.",
					"end coordinate out of bounds.",
					"obstacle over start or end.",
					"negative coordinates not allowed"};

%}

%union
{
	int num;
	Coord coord;
}

%start maze_config
%token SIZE START END OBSTACLES
%token <num> NUMBER
%type <coord> coordinate
%name-prefix "maze_yy"
%%

maze_config		: size_spec start_spec end_spec obstacle_list
				| size_spec end_spec start_spec obstacle_list
				;

size_spec		: SIZE '=' coordinate				{maze.setSize($3);}
				;

start_spec		: START '=' coordinate				{if(!maze.markStart($3)) maze_yySemanticError(errors[0]);}
				;

end_spec 		: END '=' coordinate				{if(!maze.markEnd($3)) maze_yySemanticError(errors[1]);}
				;

obstacle_list	:
				| OBSTACLES '=' coordinate_list		{if(!maze.markObstacles(obstacles)) maze_yySemanticError(errors[2]);}
				;

coordinate_list	: coordinate						{obstacles.push_back($1);}
				| coordinate_list coordinate		{obstacles.push_back($2);}
				;

coordinate 		: '(' NUMBER ',' NUMBER ')'			{if($2 < 0 || $4 < 0) maze_yySemanticError(errors[3]); else {coord.x = $2, coord.y = $4; $$ = coord;}}
				;

%%

void maze_yySemanticError(const char* str)
{
    fprintf(stderr, "Semantic Error at line %d: %s \n", maze_lineno, str);
    exit(0);
}

void maze_yyerror(const char *str)
{
	fprintf(stderr,"Error at line %d: %s \n", maze_lineno, str);
	exit(0);
}