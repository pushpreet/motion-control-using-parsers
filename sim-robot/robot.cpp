#include "robot.h"

Robot::Robot(void)
{
    position.x = 0;
    position.y = 0;
}

Robot::Robot(Maze &_maze)
{
    maze = _maze;
    goToStart();
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

void Robot::goToStart()
{
    position = maze.getStart();
}

void Robot::readEnvironment(char *environment)
{
    maze.getAdjacent(position, environment);
}

bool Robot::move(char direction)
{
    char[4] environment;

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