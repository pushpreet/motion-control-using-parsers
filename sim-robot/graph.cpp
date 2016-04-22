#include "graph.h"
#include <queue>
#include <map>
#include <stdio.h>

typedef std::map<Node*, bool> dict;

Graph::Graph(void)
{
    root = NULL;
}

Node* Graph::getNode(Coord pos)
{
    if (root == NULL)
        return NULL;

    dict isVisited;
    std::queue<Node*> nodes;

    nodes.push(root);
    isVisited[root] = false;

    Node *temp;

    while(!nodes.empty())
    {
        temp = nodes.front();
        nodes.pop();

        if (isVisited[temp]) continue;

        else if (temp->position.x == pos.x && temp->position.y == pos.y)
            return temp;

        else
        {
            if (temp->up != NULL)
            {
                isVisited[temp->up] = false;
                nodes.push(temp->up);
            }

            if (temp->down != NULL)
            {
                isVisited[temp->down] = false;
                nodes.push(temp->down);
            }

            if (temp->left != NULL)
            {
                isVisited[temp->left] = false;
                nodes.push(temp->left);
            }

            if (temp->right != NULL)
            {
                isVisited[temp->right] = false;
                nodes.push(temp->right);
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
            root = new Node;
            temp = new Node;
            temp->position.x = pos.x;
            temp->position.y = pos.y;
            temp->visited = true;
        }
        else
            return false;
    }
    else
        temp->visited = true;

    if (edges[0] == 'u') temp->up    = new Node(pos.x-1, pos.y);
    if (edges[1] == 'd') temp->down  = new Node(pos.x+1, pos.y);
    if (edges[2] == 'l') temp->left  = new Node(pos.x, pos.y-1);
    if (edges[3] == 'r') temp->right = new Node(pos.x, pos.y+1);

    if (pos.x == 0 && pos.y == 0)
    {
        root = temp;
        //delete temp;
    }

    return true;
}