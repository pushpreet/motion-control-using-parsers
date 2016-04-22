#include "controller.h"

extern char command;
extern bool reached;
extern "C" int robot_yyparse();
extern void scan_string(const char*);

Controller::Controller(void)
{
    robot = NULL;
}

Controller::Controller(Robot *robot)
{
    robot = robot;
}

void Controller::mapMaze()
{
    char status[22];
    reached = false;

    std::stack<char> trace;

    while(!reached)
    {
        robot->getStatusMessage(status);

        scan_string(status);
        robot_yyparse();

        robot->move(command);
    }
}

bool Controller::isVisited(Coord pos)
{
    return graph.getNode(pos)->visited;
}

bool Controller::isVisited(int x, int y)
{
    return graph.getNode(x, y)->visited;
}

bool Controller::visitNode(Coord pos, char* edges)
{
    return graph.visitNode(pos, edges);
}