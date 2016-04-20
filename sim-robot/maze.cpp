#include "maze.h"

Maze::Maze(void)
{
	rows = 0;
	columns = 0;
	start.x = -1;
	start.y = -1;
	end.x = -1;
	end.y = -1;
}

Maze::Maze(int _rows, int _columns)
{
	rows = _rows;
	columns = _columns;
	start.x = -1;
	start.y = -1;
	end.x = -1;
	end.y = -1;
}

bool Maze::setSize(int _rows, int _columns)
{
	rows = _rows;
	columns = _columns;
}

bool Maze::setSize(Coord size)
{
	rows = size.x;
	columns = size.y;
}

bool Maze::markStart(int x, int y)
{
	if (x >= 0 && x < rows && y >= 0 && y < columns)
	{
		start.x = x;
		start.y = y;

		return true;
	}
	else
		return false;
}

bool Maze::markEnd(int x, int y)
{
	if (x >= 0 && x < rows && y >= 0 && y < columns)
	{
		end.x = x;
		end.y = y;

		return true;
	}
	else
		return false;
}

bool Maze::markStart(Coord _start)
{
	if (_start.x >= 0 && _start.x < rows && _start.y >= 0 && _start.y < columns)
	{
		start.x = _start.x;
		start.y = _start.y;

		return true;
	}
	else
		return false;
}

bool Maze::markEnd(Coord _end)
{
	if (_end.x >= 0 && _end.x < rows && _end.y >= 0 && _end.y < columns)
	{
		start.x = _end.x;
		start.y = _end.y;

		return true;
	}
	else
		return false;
}

bool Maze::markObstacles(Coord* _obstacles, int count)
{
	for (int i = 0; i < count; ++i)
		if (_obstacles[i].x < 0 || _obstacles[i].x >= rows
				|| _obstacles.y < 0 || _obstacles[i].y >= columns)
			return false;

	for (int i = 0; i < count; ++i)
		obstacles.push_back(_obstacles[i])

	return true;
}

bool Maze::markObstacles(std::vector<Coord> _obstacles)
{
	for (int i = 0; i < _obstacles.size(); ++i)
		if (_obstacles[i].x < 0 || _obstacles[i].x >= rows
				|| _obstacles.y < 0 || _obstacles[i].y >= columns)
			return false;

	obstacles = _obstacles;

	return true;
}

Coord Maze::getStart()
{
	return start;
}

Coord Maze::getEnd()
{
	return end;
}

void Maze::getStart(int &x, int &y)
{
	x = start.x;
	y = start.y;
}

void Maze::getEnd(int &x, int &y)
{
	x = end.x;
	y = end.y;
}

bool Maze::getAdjacent(int x, int y, char* adj)
{
	if (x < 0 || x >= rows || y < 0 || y >= columns)
		return false;

	adj = "0000";

	Coord top, bottom, left, right;

	top.x = (x == 0) ? 0 : (x - 1);
	top.y = y;
	bottom.x = (x == (rows-1)) ? (rows-1) : x + 1;
	bottom.y = y;
	left.x = x;
	left.y = (y == 0) ? 0 : (y - 1);
	right.x = x;
	right.y = (y == (columns-1)) ? (columns-1) : y + 1;


	for (int i = 0; i < obstacles.size(); ++i)
	{
		switch (obstacles[i])
		{
			case top:
				adj[0] = '1';
				break;

			case bottom:
				adj[1] = '1';
				break;

			case left:
				adj[2] = '1';
				break;

			case right:
				adj[3] = '1';
				break;
		}
	}

	if (x == 0)				adj[0] = '1';
	if (x == (rows-1))		adj[1] = '1';
	if (y == 0)				adj[3] = '1';
	if (y == (columns-1))	adj[4] = '1';

	return true;
}

bool Maze::getAdjacent(Coord pos, char* adj)
{
	if (pos.x < 0 || pos.x >= rows || pos.y < 0 || pos.y >= columns)
		return false;

	adj = "0000";

	Coord top, bottom, left, right;

	top.x = (pos.x == 0) ? 0 : (pos.x - 1);
	top.y = pos.y;
	bottom.x = (pos.x == (rows-1)) ? (rows-1) : pos.x + 1;
	bottom.y = pos.y;
	left.x = pos.x;
	left.y = (pos.y == 0) ? 0 : (pos.y - 1);
	right.x = pos.x;
	right.y = (pos.y == (columns-1)) ? (columns-1) : pos.y + 1;


	for (int i = 0; i < obstacles.size(); ++i)
	{
		switch (obstacles[i])
		{
			case top:
				adj[0] = '1';
				break;

			case bottom:
				adj[1] = '1';
				break;

			case left:
				adj[2] = '1';
				break;

			case right:
				adj[3] = '1';
				break;
		}
	}

	if (pos.x == 0)				adj[0] = '1';
	if (pos.x == (rows-1))		adj[1] = '1';
	if (pos.y == 0)				adj[3] = '1';
	if (pos.y == (columns-1))	adj[4] = '1';

	return true;
}