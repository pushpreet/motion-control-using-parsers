#include "controller.h"

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
    bool reached = false;

    while(!reached)
    {
        robot->getStatusMessage(status);

        yy_scan_string(status);
        robot_yyparse();

        robot->move(command);
    }
}