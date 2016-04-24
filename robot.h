#pragma once

#include "maze.h"
#include "coord.h"

#define UP      'u'
#define DOWN    'd'
#define LEFT    'l'
#define RIGHT   'r'

class Robot
{
private:
    Coord position;
    Maze *maze;

public:
    Robot(void);
    Robot(Maze *_maze);

    Coord getPosition();
    void getPosition(int &x, int &y);

    void readEnvironment(char *environment);
    bool move(char direction);
    void getStatusMessage(char *msg);
};