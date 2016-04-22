#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"
#include "robot.h"
#include "graph.h"

extern "C" int maze_yyparse();
extern "C" FILE *maze_yyin;
extern Maze maze;

bool parseMaze(char *filename)
{
	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Cannot open %s. \n", filename);
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
	if (argc != 2)
	{
		printf("Incorrect Usage. Try ./a.out <filename> \n");
		exit(0);
	}

	if (!parseMaze(argv[1]))
		exit(0);

	// Robot robot(&maze);

	// char adj[5];
	// Coord coord;
	// char status[23];

	// robot.move(DOWN);
	// robot.move(LEFT);
	// coord = robot.getPosition();
	// robot.readEnvironment(adj);

	// printf("(%d, %d)\n", coord.x, coord.y);
	// printf("%s\n", adj);

	// robot.getStatusMessage(status);

	// printf(status);

	Graph graph;
	Coord pos;
	char edges[5];

	pos.x = 0;
	pos.y = 0;
	strcpy(edges, "u-lr");

	graph.visitNode(pos, edges);

	if (graph.getNode(pos) == NULL)
		printf("error\n");

    return 0;
}