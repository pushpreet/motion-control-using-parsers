#pragma once
#include <stack>

#include "coord.h"
#include "robot.h"
#include "graph.h"

class Controller
{
private:
    Robot *robot;
    Graph graph;

    Coord end;

public:
    Controller(void);
    Controller(Robot *robot);

    void markEnd();
    void mapMaze();
    bool traverse(const char* path);
    bool traverseShortest(Coord _start, Coord _end);
    bool traverseStartToEnd();
    bool isVisited(Coord pos);
    bool isVisited(int x, int y);
    bool visitNode(Coord pos, char* edges);
};