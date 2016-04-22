#pragma once
#include <stack>

#include "robot.h"
#include "graph.h"

class Controller
{
private:
    Robot *robot;
    Graph graph;

public:
    Controller(void);
    Controller(Robot *robot);

    void mapMaze();
    bool isVisited(Coord pos);
    bool isVisited(int x, int y);
    bool visitNode(Coord pos, char* edges);
};