#include "graph.h"
#include <queue>
#include <map>
#include <stdio.h>

typedef std::map<Node *, bool> dict;
typedef std::map<Node *, char> trace;

bool checkVisited(dict _dict, Node *node)
{
    if (_dict.find(node) == _dict.end())
        return false;

    else
        return _dict[node];
}

Graph::Graph(void)
{
    root = NULL;
}

Node* Graph::getNode(Coord pos)
{
    if (root == NULL)
        return NULL;

    if (pos.x == 0 && pos.y == 0)
        return root;

    dict isVisited;
    std::queue<Node*> nodes;

    nodes.push(root);
    isVisited[root] = false;

    Node *temp;

    while(!nodes.empty())
    {
        temp = nodes.front();
        nodes.pop();

        if (temp->position.x == pos.x && temp->position.y == pos.y)
            return temp;

        else
        {
            if ((temp->up != NULL) && (!checkVisited(isVisited, temp->up)))
            {
                isVisited[temp->up] = false;
                nodes.push(temp->up);
            }

            if ((temp->down != NULL) && (!checkVisited(isVisited, temp->down)))
            {
                isVisited[temp->down] = false;
                nodes.push(temp->down);
            }

            if ((temp->left != NULL) && (!checkVisited(isVisited, temp->left)))
            {
                isVisited[temp->left] = false;
                nodes.push(temp->left);
            }

            if ((temp->right != NULL) && (!checkVisited(isVisited, temp->right)))
            {
                isVisited[temp->right] = false;
                nodes.push(temp->right);
            }
        }

        isVisited[temp] = true;
    }

    return NULL;
}

Node* Graph::getNode(int x, int y)
{
    if (root == NULL)
        return NULL;

    if (x == 0 && y == 0)
        return root;

    dict isVisited;
    std::queue<Node*> nodes;

    nodes.push(root);
    isVisited[root] = false;

    Node *temp;

    while(!nodes.empty())
    {
        temp = nodes.front();
        nodes.pop();

        if (temp->position.x == x && temp->position.y == y)
            return temp;

        else
        {
            if ((temp->up != NULL) && (!checkVisited(isVisited, temp->up)))
            {
                isVisited[temp->up] = false;
                nodes.push(temp->up);
            }

            if ((temp->down != NULL) && (!checkVisited(isVisited, temp->down)))
            {
                isVisited[temp->down] = false;
                nodes.push(temp->down);
            }

            if ((temp->left != NULL) && (!checkVisited(isVisited, temp->left)))
            {
                isVisited[temp->left] = false;
                nodes.push(temp->left);
            }

            if ((temp->right != NULL) && (!checkVisited(isVisited, temp->right)))
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
            temp = new Node(0, 0);
            temp->visited = true;
            root = temp;
        }
        else
            return false;
    }
    else if (temp != NULL)
        if(temp->visited) return true;
    else
        temp->visited = true;

    for (int i = 0; edges[i] != '\0'; i++)
	{
        if (edges[i] == 'u')
            temp->up = (getNode(pos.x-1, pos.y) == NULL) ? new Node(pos.x-1, pos.y) : getNode(pos.x-1, pos.y);
        if (edges[i] == 'd')
            temp->down = (getNode(pos.x+1, pos.y) == NULL) ? new Node(pos.x+1, pos.y) : getNode(pos.x+1, pos.y);
        if (edges[i] == 'l')
            temp->left = (getNode(pos.x, pos.y-1) == NULL) ? new Node(pos.x, pos.y-1) : getNode(pos.x, pos.y-1);
        if (edges[i] == 'r')
            temp->right = (getNode(pos.x, pos.y+1) == NULL) ? new Node(pos.x, pos.y+1) : getNode(pos.x, pos.y+1);
    }

    if (pos.x == 0 && pos.y == 0)
        root = temp;

    printf("Visited (%d, %d) - ", temp->position.x, temp->position.y);

    return true;
}

const char* Graph::shortestPath(Coord _start, Coord _dest)
{
    Node *start = getNode(_start);
    Node *dest = getNode(_dest);

    dict isVisited;
    std::queue<Node*> nodes;

    nodes.push(start);
    isVisited[start] = true;

    Node *temp;

    trace backTrack;

    while(!nodes.empty())
    {
        temp = nodes.front();
        nodes.pop();

        if (temp == dest) break;

        if ((temp->up != NULL) && (!checkVisited(isVisited, temp->up)))
        {
            isVisited[temp->up] = true;
            nodes.push(temp->up);
            backTrack[temp->up] = 'd';
        }

        if ((temp->down != NULL) && (!checkVisited(isVisited, temp->down)))
        {
            isVisited[temp->down] = true;
            nodes.push(temp->down);
            backTrack[temp->down] = 'u';
        }

        if ((temp->left != NULL) && (!checkVisited(isVisited, temp->left)))
        {
            isVisited[temp->left] = true;
            nodes.push(temp->left);
            backTrack[temp->left] = 'r';
        }

        if ((temp->right != NULL) && (!checkVisited(isVisited, temp->right)))
        {
            isVisited[temp->right] = true;
            nodes.push(temp->right);
            backTrack[temp->right] = 'l';
        }
    }

    std::string path;

    while(temp != start)
    {
        if (backTrack[temp] == 'u') {temp = temp->up; path.insert(0, 1, 'd');}
        else if (backTrack[temp] == 'd') {temp = temp->down; path.insert(0, 1, 'u');}
        else if (backTrack[temp] == 'l') {temp = temp->left; path.insert(0, 1, 'r');}
        else if (backTrack[temp] == 'r') {temp = temp->right; path.insert(0, 1, 'l');}
    }

    return path.c_str();
}