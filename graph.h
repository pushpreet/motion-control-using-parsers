#pragma once

#include <cstddef>
#include <stdio.h>
#include <string>
#include "coord.h"

extern bool verbose;

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
        if (verbose) printf("(0, 0) ");
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
        if (verbose) printf("(%d, %d) ", x, y);
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
    const char* shortestPath(Coord _start, Coord _dest);
};