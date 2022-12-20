//
// Splay Tree class implementation
//

#ifndef P3_SPLAYTREE_H
#define P3_SPLAYTREE_H

#include <chrono>
#include <string>
#include <iostream>
#include "Node.h"
using namespace std;

class SplayTree
{
private:
    int traversalCount;
public:
    Node<int>* root;

    // constructor
    SplayTree();

    // destructor
    ~SplayTree();

    void insertOnly(Node<int>*, int);
    Node<int>* searchOnly(Node<int>*, int);
    void removeOnly(Node<int>*, int);

    void insert(Node<int>*, int);
    void search(Node<int>*, int);
    void remove(Node<int>*, int);

    void displayTree(Node<int>* root);
    void deallocateTree(Node<int>*);

    Node<int>* rotateRight(Node<int>*);
    Node<int>* rotateLeft(Node<int>*);

    int getTraversalCount();

    void splay(int);

};

SplayTree::SplayTree() {
    root = nullptr;
    traversalCount = 0;
}

SplayTree::~SplayTree() {
//    cout << "Entered destructor\n";
    deallocateTree(root);
}

void SplayTree::insertOnly(Node<int> *currentRoot, int data) {
    if(root == nullptr) {
        // base case
        root = new Node<int>(data);
    }
    else if(data > currentRoot->info){
        // traverse right subtree
        traversalCount++;
        if(currentRoot->rightChild == nullptr){
            // reached the leaf, insert the node
            traversalCount++;
            currentRoot->rightChild = new Node<int>(data, currentRoot);
        }
        else {
            insertOnly(currentRoot->rightChild, data);
        }
    }
    else{ // traverse left subtree
        traversalCount++;
        if(currentRoot->leftChild == nullptr){
            // reached the leaf, insert the node
            currentRoot->leftChild = new Node<int>(data, currentRoot);
        }
        else {
            insertOnly(currentRoot->leftChild, data);
        }
    }
}

Node<int> *SplayTree::searchOnly(Node<int> *currentRoot, int lookingFor) {
    if(root == nullptr) {
        cout << "Tree is empty\n";
        return root;
    }
    else if(currentRoot->info == lookingFor){
        traversalCount++;
//        cout << "Found " << currentRoot->info << "!\n";
        return currentRoot;
    }
    else if(lookingFor > currentRoot->info){
        traversalCount++;
        if (currentRoot->rightChild == nullptr){
            return currentRoot;
        }
        else {
            return searchOnly(currentRoot->rightChild, lookingFor);
        }
    }
    else{
        traversalCount++;
        if (currentRoot->leftChild == nullptr) {
            return currentRoot;
        }
        else {
            return searchOnly(currentRoot->leftChild, lookingFor);
        }
    }
}

void SplayTree::removeOnly(Node<int> *currentRoot, int data) {
    if (currentRoot != nullptr){
        // node is not null
        if(currentRoot->info < data){
            // traverse right subtree
            traversalCount++;
            removeOnly(currentRoot->rightChild, data);
        }
        else if(currentRoot->info > data){
            // traverse left subtree
            traversalCount++;
            removeOnly(currentRoot->leftChild, data);
        }

        else if(currentRoot->rightChild != nullptr && currentRoot->leftChild != nullptr){
            // Case 3: node to be deleted has two children
            Node<int> *rightMin = currentRoot->rightChild;
            while(rightMin->leftChild != nullptr){
                traversalCount++;
                // traverse tree to find the minimum of the right subtree
                rightMin = rightMin->leftChild;
            }
            // swap values
            int temp = currentRoot->info;
            currentRoot->info = rightMin->info;
            rightMin->info = temp;
            removeOnly(currentRoot->rightChild, temp);
        } // end case 3
        else{
            // cases 1 and 2, node has 0 and 1 child
            Node<int>* deleteThis = currentRoot;
            if(currentRoot == currentRoot->parent->leftChild){
                // node is the leftChild of parent node
                if(currentRoot->rightChild == nullptr && currentRoot->leftChild == nullptr){
                    // node has no children
                    currentRoot->parent->leftChild = nullptr;
                }
                else if(currentRoot->leftChild != nullptr){
                    // node has a left child
                    currentRoot->parent->leftChild = currentRoot->leftChild;
                    currentRoot->leftChild->parent = currentRoot->parent;
                }
                else{
                    // node has a right child
                    currentRoot->parent->leftChild = currentRoot->rightChild;
                    currentRoot->rightChild->parent = currentRoot->parent;
                }
            } // end node being left child
            else if(currentRoot == currentRoot->parent->rightChild){
                // node is the right child of parent node
                if(currentRoot->rightChild == nullptr && currentRoot->leftChild == nullptr){
                    currentRoot->parent->rightChild = nullptr;
                }
                else if(currentRoot->leftChild != nullptr){
                    currentRoot->parent->rightChild = currentRoot->leftChild;
                    currentRoot->leftChild->parent = currentRoot->parent;
                }
                else{
                    currentRoot->parent->rightChild = currentRoot->rightChild;
                    currentRoot->rightChild->parent = currentRoot->parent;
                }
            } // end node being right child

            // delete node
            delete deleteThis;
            if(currentRoot == root){
                root = nullptr;
            }
        } // end Cases 1 and 2
    } // end currentRoot being not null

} // END removeOnly function for class SplayTree

void SplayTree::displayTree(Node<int> *r) {
    if(r == nullptr){
        cout << "[]";
        return;
    }
    else { // similar to deallocate if stat
        cout << "[" << r->info;
        if(r->leftChild != nullptr || r->rightChild != nullptr) {
            displayTree(r->leftChild);
            displayTree(r->rightChild);
        }
        cout << "]";
    }
}

void SplayTree::deallocateTree(Node<int> *node) {
    if(node == nullptr){
        return;
    }
    else{
        deallocateTree(node->leftChild);
        deallocateTree(node->rightChild);
        removeOnly(root, node->info);
    }
    root = nullptr;

}

Node<int> *SplayTree::rotateRight(Node<int> *current) {
    Node<int> *temp = current->leftChild;
    current->leftChild = temp->rightChild;
    if (temp->rightChild != nullptr) {
        temp->rightChild->parent = current;
    }
    temp->parent = current->parent;
    if (current->parent == nullptr) {
        root = temp;
    } else if (current == current->parent->leftChild) {
        current->parent->leftChild = temp;
    } else {
        current->parent->rightChild = temp;
    }
    temp->rightChild = current;
    current->parent = temp;
    return temp;
}

Node<int> *SplayTree::rotateLeft(Node<int> *current) {
    Node<int> *temp = current->rightChild;
    current->rightChild = temp->leftChild;
    if (temp->leftChild != nullptr) {
        temp->leftChild->parent = current;
    }
    temp->parent = current->parent;
    if (current->parent == nullptr) {
        root = temp;
    } else if (current == current->parent->leftChild) {
        current->parent->leftChild = temp;
    } else {
        current->parent->rightChild = temp;
    }
    temp->leftChild = current;
    current->parent = temp;
    return temp;
}

int SplayTree::getTraversalCount() {
    return traversalCount;
}

void SplayTree::splay(int data) {
    Node<int> *splayThis = searchOnly(root, data);
    while (splayThis->parent != nullptr) {
        // splayThis is not the root

        if (splayThis->parent->parent != nullptr) {

            // perform double rotation
            if (splayThis->parent == splayThis->parent->parent->leftChild) {
                // splayThis' parent is the left child
                if (splayThis == splayThis->parent->leftChild) {
                    // zig zig, splayThis is the left grandchild
                    // perform first right ro, second after conditional
                    splayThis->parent = rotateRight(splayThis->parent->parent);
                } else {
                    // splayThis is right child of left child, zig zag
                    // perform first left ro, second after conditional
                    splayThis = rotateLeft(splayThis->parent);
                }
                // perform second ro
                splayThis = rotateRight(splayThis->parent);
                traversalCount += 1;
            } else {
                // splayThis' parent is the right child
                if (splayThis == splayThis->parent->rightChild) {
                    // zig zig, splayThis is the right child of the right child
                    // perform first ro
                    splayThis->parent = rotateLeft(splayThis->parent->parent);
                } else {
                    // splayThis is the left child of the right child
                    // perform first ro
                    splayThis = rotateRight(splayThis->parent);
                }
                // perform second ro
                splayThis = rotateLeft(splayThis->parent);
                traversalCount += 1;
            }
        } // END double rotations
        else if (splayThis->parent == root) {
            // splayThis is child of root, one rotation
            if (splayThis == splayThis->parent->leftChild) {
                // left child, rotate right
                splayThis = rotateRight(splayThis->parent);
                traversalCount += 1;
            } else {
                //splayThis is right child, rotate left
                splayThis = rotateLeft(splayThis->parent);
                traversalCount += 1;
            }
        } // END single rotations
    } // END while splayThis not the root
} // END splay function

void SplayTree::insert(Node<int> * node, int data) {
    insertOnly(node, data);
    splay(data);
}

void SplayTree::search(Node<int> * node, int data) {
    splay(data);
}

void SplayTree::remove(Node<int> * node, int data) {
    splay(data);
    //cout << "REMoving\n";
    removeOnly(root, data);
}

#endif //P3_SPLAYTREE_H
