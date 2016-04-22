#include "controller.h"

extern char command;
extern bool reached;
extern bool completed;
extern "C" int robot_yyparse();
extern void scan_string(const char*);

Controller::Controller(void)
{
    robot = NULL;
}

Controller::Controller(Robot *_robot)
{
    robot = _robot;
}

void Controller::mapMaze()
{
    char status[23];
    reached = false;

    std::stack<char> trace;

    while(!completed)
    {
        robot->getStatusMessage(status);
        //printf("%s", status);

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
                //printf("%s", status);
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