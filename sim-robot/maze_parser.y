%{
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "maze.h"

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE * yyin;

void yyerror(const char *str);

Maze maze;
Coord coord;
std::vector<Coord> obstacles;
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

%%

maze_config		: size_spec start_spec end_spec obstacle_list
				| size_spec end_spec start_spec obstacle_list
				;

size_spec		: SIZE '=' coordinate				{maze.setSize($3);}
				;

start_spec		: START '=' coordinate				{maze.markStart($3);}
				;

end_spec 		: END '=' coordinate				{maze.markEnd($3);}
				;

obstacle_list	: 
				| OBSTACLES '=' coordinate_list		{maze.markObstacles(obstacles);}
				;

coordinate_list	: coordinate						{obstacles.push_back($1);}
				| coordinate_list coordinate		{obstacles.push_back($2);}
				;

coordinate 		: '(' NUMBER ',' NUMBER ')'			{coord.x = $2, coord.y = $4; $$ = coord;}
				;

%%

void yyerror(const char *str)
{
	fprintf(stderr,"error: %s\n",str);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Incorrect Usage. Try ./a.out <filename> \n");
		exit(0);
	}

	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Cannot open %s. \n", argv[1]);
		exit(0);
	}

	yyin = file;

    do
    {
        yyparse();
    } while(!feof((yyin)));

    fclose(file);

    Coord coord;

    coord = maze.getStart();
    printf("Start : %d, %d\n", coord.x, coord.y);

   	coord = maze.getEnd();
    printf("End : %d, %d\n", coord.x, coord.y);

    return 0;
}