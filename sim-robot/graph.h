#pragma once

#include <cstddef>
#include <stdio.h>
#include "coord.h"

struct Node
{
    Coord position;
    bool visited;

    Node *up;
    Node *down;
    Node *left;
    Node *right;

    Node(void)
    {
        //printf("Node created: (0, 0)\n");
        position.x = 0;
        position.y = 0;
        visited = false;

        up = NULL;
        down = NULL;
        left = NULL;
        right = NULL;
    }

    Node(int x, int y)
    {
        //printf("Node created: (%d, %d)\n", x, y);
        position.x = x;
        position.y = y;
        visited = false;

        up = NULL;
        down = NULL;
        left = NULL;
        right = NULL;
    }
};

class Graph
{
private:
    Node *root;

public:
    Graph(void);

    Node* getNode(Coord pos);
    Node* getNode(int x, int y);
    bool visitNode(Coord pos, char *edges);
};