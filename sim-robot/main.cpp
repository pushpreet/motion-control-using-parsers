#include <stdio.h>
#include <stdlib.h>

#include "maze.h"

extern "C" int maze_yyparse();
extern "C" FILE * maze_yyin;
extern Maze maze;

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

	maze_yyin = file;

    do
    {
        maze_yyparse();
    } while(!feof((maze_yyin)));

    fclose(file);

	Coord coord;
	coord = maze.getStart();

	printf("( %d, %d)\n", coord.x, coord.y);

    return 0;
}