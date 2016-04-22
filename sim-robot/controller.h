#pragma once
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
};