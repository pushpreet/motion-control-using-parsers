#pragma once

#include <vector>
#include <stdio.h>

#include "coord.h"

class Maze
{
private:
	int rows;
	int columns;
	Coord start;
	Coord end;
	std::vector<Coord> obstacles;

public:
	//constructors
	Maze(void);
	Maze(int _rows, int _columns);

	//setters
	bool setSize(int _row, int _columns);
	bool setSize(Coord size);
	bool markStart(int x, int y);
	bool markEnd(int x, int y);
	bool markStart(Coord _start);
	bool markEnd(Coord _end);
	bool markObstacles(Coord* _obstacles, int count);
	bool markObstacles(std::vector<Coord> _obstacles);

	//getters
	Coord getStart();
	Coord getEnd();
	void getStart(int &x, int &y);
	void getEnd(int &x, int &y);

	bool getAdjacent(int x, int y, char* adj);
	bool getAdjacent(Coord pos, char* adj);

	void printMaze();
};