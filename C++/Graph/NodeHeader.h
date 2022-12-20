//
// Created by Aidan Pizzo on 11/30/22.
//

#ifndef P4_NODEHEADER_H
#define P4_NODEHEADER_H

#include <chrono>
#include <string>
#include <iostream>
#include "Node.h"
using namespace std;

class NodeHeader
{
public:
    string title;
    Node* list;
    NodeHeader* nextHeader;


    NodeHeader();
    NodeHeader(string t);
    NodeHeader(string t, string de, int c, int i);
};

NodeHeader::NodeHeader() {
    title = "";
    list = nullptr;
    nextHeader = nullptr;
}

NodeHeader::NodeHeader(string t) {
    title = t;
    list = nullptr;
    nextHeader = nullptr;
}

NodeHeader::NodeHeader(string t, string de, int c, int i) {
    title = t;
    list = new Node(de, c);
    nextHeader = nullptr;
}

#endif //P4_NODEHEADER_H
