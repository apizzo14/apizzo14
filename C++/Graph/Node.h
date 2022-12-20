//
// Class Node for nodes of a graph's adjacency list
//

#ifndef P3_NODE_H
#define P3_NODE_H

#include <chrono>
#include <string>
#include <iostream>
using namespace std;

class Node
{
public:
    int cost;
    string dest;
    Node *next;

    Node();
    Node(string, int);
    Node(string, int, Node*);

};

Node::Node() {
    cost = 0;
    dest = "";
    next = nullptr;
}

Node::Node(string d, int c) {
    cost = c;
    dest = d;
    next = nullptr;
}

Node::Node(string d, int c, Node* n) {
    cost = c;
    dest = d;
    next = n;
}

//END declaration class Node

#endif //P3_NODE_H
