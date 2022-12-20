/*
 * Templatized class "Node" represents each node of a linked list
 *
 * Created by Aidan Pizzo
 */

#ifndef P2_NODE_H
#define P2_NODE_H

template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;

    Node();
    Node(T);

};

template<typename T>
Node<T>::Node() {
    info = T();
    next = nullptr;
}

template<typename T>
Node<T>::Node(T data) {
    info = data;
    next = nullptr;
}
//END declaration templatized class Node
#endif //P2_NODE_H
