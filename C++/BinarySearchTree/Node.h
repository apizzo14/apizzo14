//
// Templatized Class Node for nodes of a BST
//

#ifndef P3_NODE_H
#define P3_NODE_H

#include <chrono>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T info;
    Node<T> *rightChild;
    Node<T> *leftChild;
    Node<T> *parent;

    Node();
    Node(T);
    Node(T, Node<T>*);

};

template<typename T>
Node<T>::Node() {
    info = T();
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

template<typename T>
Node<T>::Node(T data) {
    info = data;
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

template<typename T>
Node<T>::Node(T data, Node<T> * p) {
    info = data;
    leftChild = nullptr;
    rightChild = nullptr;
    parent = p;
}
//END declaration templatized class Node

#endif //P3_NODE_H
