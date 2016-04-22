#include "Coord.h"

struct Node
{
    Coord position;
    bool visited;

    Node *up;
    Node *down;
    Node *left;
    Node *right;

    Node(int x, int y)
    {
        position.x = x;
        position.y = y;
        visited = false;
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