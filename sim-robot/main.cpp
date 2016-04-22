#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"
#include "robot.h"
#include "graph.h"
#include "controller.h"

extern "C" int maze_yyparse();
extern "C" FILE *maze_yyin;
extern Maze maze;

Robot robot(&maze);
Controller controller(&robot);
bool verbose = false;
bool simulate = false;

bool parseMaze(char *filename)
{
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Cannot open %s. \n", filename);
		return false;
	}

	maze_yyin = file;

    do
    {
        maze_yyparse();
    } while(!feof((maze_yyin)));

    fclose(file);

	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Incorrect Usage. Try ./a.out <filename> \n");
		exit(0);
	}

	for (int i = 2; i < argc; ++i)
	{
		if (strcmp(argv[i], "-v") || strcmp(argv[i], "-verbose"))
			verbose = true;;
		if (strcmp(argv[i], "-sim") || strcmp(argv[i], "-simulate"))
			simulate = true;
	}

	printf("\nParsing Maze... ");
	if (!parseMaze(argv[1])) exit(0);

	printf("Parsed!\n");
	maze.printMaze();

	printf("\nMapping Maze... \n");
	controller.mapMaze();

	printf("\nTraversing Shortest Path...\n");
	controller.traverseStartToEnd();

	printf("\n");
    return 0;
}