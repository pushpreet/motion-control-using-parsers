#include "graph.h"
#include <queue>
#include <map>

typedef std::map<Node*, bool> dict;

Graph::Graph(void)
{
    root = NULL;
}

Node* Graph::getNode(Coord pos)
{
    dict isVisited;
    std::queue<Node*> nodes;

    queue.push(root);
    isVisited[root] = true;

    Node *temp;

    while(!queue.empty())
    {
        temp = queue.pop();

        if (isVisited[temp]) continue;

        if (temp->position.x == pos.x && temp->position.y == pos.y)
            return temp;

        else
        {
            if (temp->up != NULL)
            {
                isVisited[temp->up] = false;
                queue.push(temp->up);
            }

            if (temp->down != NULL)
            {
                isVisited[temp->down] = false;
                queue.push(temp->down);
            }

            if (temp->left != NULL)
            {
                isVisited[temp->left] = false;
                queue.push(temp->left);
            }

            if (temp->right != NULL)
            {
                isVisited[temp->right] = false;
                queue.push(temp->right);
            }
        }

        isVisited[temp] = true;
    }

    return NULL;
}

bool Graph::visitNode(Coord pos, char *edges)
{
    Node *temp = getNode(pos);

    if (temp == NULL)
    {
        if (pos.x == 0 && pos.y == 0)
        {
            temp = new Node();
            temp->position.x = pos.x;
            temp->position.y = pos.y;
            temp->visited = true;
        }
        else
            return false;
    }
    else
        temp->visited = true;

    (edges[0] == 'u') ? temp->up    = new Node(pos.x-1, pos.y) : temp->up = NULL;
    (edges[1] == 'd') ? temp->down  = new Node(pos.x+1, pos.y) : temp->down = NULL;
    (edges[2] == 'l') ? temp->left  = new Node(pos.x, pos.y-1) : temp->left = NULL;
    (edges[3] == 'r') ? temp->right = new Node(pos.x, pos.y+1) : temp->right = NULL;

    if (pos.x == 0 && pos.y == 0)
        root = temp;

    delete temp;

    return true;
}