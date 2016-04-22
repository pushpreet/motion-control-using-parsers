#include <cstddef>
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
    bool visitNode(Coord pos, char *edges);
};