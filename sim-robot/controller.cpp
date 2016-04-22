#include "controller.h"

extern char command;
extern bool reached;
extern bool completed;
extern bool verbose;
extern "C" int robot_yyparse();
extern void scan_string(const char*);

Controller::Controller(void)
{
    robot = NULL;
    end.x = 0;
    end.y = 0;
}

Controller::Controller(Robot *_robot)
{
    robot = _robot;
    end.x = 0;
    end.y = 0;
}

void Controller::markEnd()
{
    end = robot->getPosition();
}

void Controller::mapMaze()
{
    char status[23];
    reached = false;

    std::stack<char> trace;

    while(!completed)
    {
        robot->getStatusMessage(status);
        if (verbose) printf("\n%s", status);

        scan_string(status);
        robot_yyparse();

        if (command == 't')
        {
            printf("Traceback: ");
            while(!trace.empty() && command == 't')
            {
                if (robot->move(trace.top()))
                {
                    printf("%c ", trace.top());
                    trace.pop();
                }
                else fprintf(stderr, "error: wrong trace\n");

                robot->getStatusMessage(status);
                //if (verbose) printf("\n\n%s", status);

                scan_string(status);
                robot_yyparse();
            }
            printf("\nReached (%d, %d) - ", robot->getPosition().x, robot->getPosition().y);
        }

        if (robot->move(command))
        {
            if (command == 'u') trace.push('d');
            else if (command == 'd') trace.push('u');
            else if (command == 'l') trace.push('r');
            else if (command == 'r') trace.push('l');

            printf("Move: %c\n", command);
        }
    }

    printf("Mapping Complete.\n\n");

    Coord start;
    start.x = 0;
    start.y = 0;

    printf("START: (%d, %d)\n", 0, 0);
    printf("END: (%d, %d)\n", end.x, end.y);
}

bool Controller::traverse(const char* path)
{
    for (int i  = 0; path[i] != '\0'; ++i)
    {
        printf("Reached (%d, %d) - ", robot->getPosition().x, robot->getPosition().y);

        if (!robot->move(path[i])) return false;
        else printf("Move: %c\n", path[i]);
    }

    printf("Reached (%d, %d) - ", robot->getPosition().x, robot->getPosition().y);
    printf("Destination Reached.\n");

    return true;
}

bool Controller::traverseShortest(Coord _start, Coord _end)
{
    return traverse(graph.shortestPath(_start, _end));
}

bool Controller::traverseStartToEnd()
{
    Coord start;
    start.x = 0;
    start.y = 0;

    return traverseShortest(start, end);
}

bool Controller::isVisited(Coord pos)
{
    //printf("Called isVisited for (%d, %d)\n", pos.x, pos.y);
    Node *temp = graph.getNode(pos);

    if (temp != NULL) return temp->visited;
    else return false;
}

bool Controller::isVisited(int x, int y)
{
    //printf("Called isVisited for (%d, %d)\n", x, y);
    Node *temp = graph.getNode(x, y);

    if (temp != NULL) return temp->visited;
    else return false;
}

bool Controller::visitNode(Coord pos, char* edges)
{
    //printf("Called visitNode for (%d, %d), \"%s\"\n", pos.x, pos.y, edges);
    return graph.visitNode(pos, edges);
}