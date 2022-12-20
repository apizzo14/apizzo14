//
// Binary Search Tree class implementation
//

#ifndef P3_BST_H
#define P3_BST_H

#include <chrono>
#include <string>
#include <iostream>
#include "Node.h"
using namespace std;

class BST
{
private:
    int traversalCount;
public:
    Node<int>* root;

    // constructor
    BST();

    // destructor
    ~BST();

    void insert(Node<int>*, int);
    Node<int>* search(Node<int>*, int);
    void remove(Node<int>*, int);

    void displayTree(Node<int>* root);
    void deallocateTree(Node<int>*);
    int getTraversalCount() const;

};

BST::BST() {
    root = nullptr;
    traversalCount = 0;
}

BST::~BST() {
    deallocateTree(root);
}

void BST::insert(Node<int>* currentRoot, int data) {
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
            insert(currentRoot->rightChild, data);
        }
    }
    else{ // traverse left subtree
        traversalCount++;
        if(currentRoot->leftChild == nullptr){
            // reached the leaf, insert the node
            currentRoot->leftChild = new Node<int>(data, currentRoot);
        }
        else {
            insert(currentRoot->leftChild, data);
        }
    }

} // END insert function for class BST

Node<int>* BST::search(Node<int>* currentRoot, int lookingFor) {
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
            return search(currentRoot->rightChild, lookingFor);
        }
    }
    else{
        traversalCount++;
        if (currentRoot->leftChild == nullptr) {
            return currentRoot;
        }
        else {
            return search(currentRoot->leftChild, lookingFor);
        }
    }
} // End search function for class BST

void BST::remove(Node<int>* currentRoot, int data) {
    if (currentRoot != nullptr){
        // node is not null
        if(currentRoot->info < data){
            // traverse right subtree
            traversalCount++;
            remove(currentRoot->rightChild, data);
        }
        else if(currentRoot->info > data){
            // traverse left subtree
            traversalCount++;
            remove(currentRoot->leftChild, data);
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
            remove(currentRoot->rightChild, temp);
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

} // END remove function for class BST

void BST::deallocateTree(Node<int>* node) {

    if(node == nullptr){
        return;
    }
    else{
        deallocateTree(node->leftChild);
        deallocateTree(node->rightChild);
        remove(root, node->info);
    }
    root = nullptr;

} // end function deallocateTree

void BST::displayTree(Node<int>* r) {
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

int BST::getTraversalCount() const {
    return traversalCount;
}


#endif //P3_BST_H
