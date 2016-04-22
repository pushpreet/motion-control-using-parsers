#include "robot.h"
#include <string.h>

Robot::Robot(void)
{
    position.x = 0;
    position.y = 0;
}

Robot::Robot(Maze *_maze)
{
    position.x = 0;
    position.y = 0;
    maze = _maze;
}

Coord Robot::getPosition()
{
    return position;
}

void Robot::getPosition(int &x, int &y)
{
    x = position.x;
    y = position.y;
}

void Robot::readEnvironment(char *environment)
{
    maze->getAdjacent(position, environment);
}

bool Robot::move(char direction)
{
    char environment[5];

    readEnvironment(environment);

    switch(direction)
    {
        case UP:
            if (environment[0] == '0')
            {
                position.x--;
                return true;
            }
            break;

        case DOWN:
            if (environment[1] == '0')
            {
                position.x++;
                return true;
            }
            break;

        case LEFT:
            if (environment[2] == '0')
            {
                position.y--;
                return true;
            }
            break;

        case RIGHT:
            if (environment[3] == '0')
            {
                position.y++;
                return true;
            }
            break;
    }

    return false;
}

void Robot::getStatusMessage(char *msg)
{
    int dirIndex = 0;
    char nodeType[6];
    char environment[5], directions[5];
    Coord endNode;

    readEnvironment(environment);

    if (environment[0] == '0') directions[dirIndex++] = 'u';
    if (environment[1] == '0') directions[dirIndex++] = 'd';
    if (environment[2] == '0') directions[dirIndex++] = 'l';
    if (environment[3] == '0') directions[dirIndex++] = 'r';

    directions[dirIndex] = '\0';

    endNode = maze->getEnd();

    if (position.x == 0 && position.y == 0) strcpy(nodeType, "START");
    else if (position.x == endNode.x && position.y == endNode.y) strcpy(nodeType, "END");
    else strcpy(nodeType, "NODE");

    sprintf(msg, "%s: (%d, %d), \"%s\"\n", nodeType, position.x, position.y, directions);
}