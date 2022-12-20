//
// This class creates an adjacency list to represent a graph
//

#ifndef P4_GRAPH_H
#define P4_GRAPH_H

#include <chrono>
#include <string>
#include <iostream>
#include "Node.h"
#include "NodeHeader.h"
#include "PriorityQueue.h"
using namespace std;

class adjacencyList
{
public:
    NodeHeader* contents;
    int numLists;

    void addNode(string, string, int);
    void printGraph();
    int getIndex(string);
    int getShortestPath(string, string);

    adjacencyList();
};

adjacencyList::adjacencyList() {
    contents = nullptr;
    numLists = 0;
}

void adjacencyList::addNode(string t, string d, int c) {
    if(contents == nullptr){
        // graph is empty
        contents = new NodeHeader(t, d, c, numLists);
        numLists +=1;
    }
    else{
        // graph is not empty, traverse
        NodeHeader *tempHeader = contents; // not null

        // traverse to list or end of headers
        while(tempHeader->title != t && tempHeader->nextHeader != nullptr){
            tempHeader = tempHeader->nextHeader;
        }

        // if current header is not null, add node to existing list
        if(tempHeader->title == t){
            Node* temp = tempHeader->list;
            while(temp->next != nullptr){
                // traverse to end of list
                temp = temp->next;
            }
            temp->next = new Node(d,c);
        }

        // if tempHeader is null, create new list
        else if(tempHeader->nextHeader == nullptr){
            tempHeader->nextHeader = new NodeHeader(t, d, c, numLists);
            numLists += 1;
        }

    } // end non-empty list condition

} // end function addNode

void adjacencyList::printGraph() {
    NodeHeader *tempHeader;
    Node *temp;

    tempHeader = contents;
    // traverse list headers
    while(tempHeader != nullptr){
        cout << tempHeader->title << ": ";
        // print out each node of list
        temp = tempHeader->list;
        while(temp != nullptr){
            cout << temp->dest << " " << temp->cost << " -> ";
            temp = temp->next;
        }
        cout << endl;
        tempHeader = tempHeader->nextHeader;
    }
}

int adjacencyList::getShortestPath(string st, string en) {
    int pathCost = 0;
    // add starting node to queue
    PriorityQueue q1 = PriorityQueue();
    q1.enqueue(st, 0);
//    q1.printQueue();

    // while queue is not empty and popped/dequeued value is not en (end node)
    while(q1.length != 0){
        // dequeue first priority node
        Node* inspect = q1.dequeue();
//        cout << inspect->dest << " "; cout << endl;
        if(inspect->dest == en) {
            pathCost = inspect->cost;
            break;
        }
        // enqueue adjacent nodes with their values going through graph list
        NodeHeader *temp = contents;
        while(temp->title != inspect->dest){
            // traverse to adj list of dequeued object
            temp = temp->nextHeader;
        }
        Node* temp2 = temp->list;
        while(temp2 != nullptr){
            q1.enqueue(temp2->dest, inspect->cost+temp2->cost);
            temp2 = temp2->next;
        }
//        q1.printQueue();
    } // end non empty priority queue
    return pathCost;
}

#endif //P4_GRAPH_H
