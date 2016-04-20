#pragma once

struct Coord
{
	int x;
	int y;

	bool operator== (Coord coord)
	{
		if (x == coord.x && y == coord.y)
			return true;
		else
			return false;
	}
};