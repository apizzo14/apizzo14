/*
 * This class is a hash table that uses the chaining method to handle collisions
 *
 * Created by Aidan Pizzo
 */

#ifndef P2_HASHTABLECHAINING_H
#define P2_HASHTABLECHAINING_H

#include "Node.h"
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

class HashTableChain
{
private:
    int size;
    Node<string>* table;

public:
    // constructor
    HashTableChain(int);

    // destructor
    ~HashTableChain();

    // insert word into hash table dict
    void insert(string);

    // hash function returns index of word
    int hashFunction(string);

    // print for testing
    void printTable();

    // check to see if word is in table
    int spellCheck(string);

};

HashTableChain::HashTableChain(int tableSize) {
    size = tableSize;
    table = new Node<string>[size];

    // initialize table with default values
    for (int i = 0; i < tableSize; i++){
        table[i].next = nullptr;
        table[i].info = "";
    }
}

void HashTableChain::insert(string DictWord) {
//    cout << "Entering insert method\n";

    // get index of hash table using hash function function
    int index = hashFunction(DictWord);

    // if index is empty (no collision) add dict info to first slot
    if(table[index].info == ""){
        table[index].info = DictWord;
    }
    else{ // collision, add dict info to next open link in chain
//        cout << "Collision!\n";
        Node<string> *current = &table[index];
        // traverse linked list to get to last entry
        while(current->next != nullptr){
            current = current->next;
        }
//        cout << "Ending traversal\n";

        // add new node with dictionary info
        current->next = new Node<string>(DictWord); // WHY IS THIS CAUSING A SEG FAULT???????????????????????
//        cout << "Did it!\n";
    } // END else condition: linked list is not empty

}// END insert function


int HashTableChain::hashFunction(string dictWord) {
    unsigned int hashValue = 0;
    for(char ch : dictWord)
        hashValue = 37 * hashValue + ch;
    return hashValue % size;
}


void HashTableChain::printTable() {
    Node<string> *current = nullptr;
    for(int i=0; i < size; i++) {
        cout << i << " --> " << table[i].info;
        if (table[i].next != nullptr) {
            // if there are other nodes in linked list, print info for all of them
            current = table[i].next;
            while(current != nullptr){
                cout << " --> " << current->info;
                current = current->next;
            } // end while loop traversing linked list at index i
        }
        cout << endl;
    } // END for loop traversing table
}


int HashTableChain::spellCheck(string dictWord) {
    int spellCheck = 1;
    int index = hashFunction(dictWord);
    if(table[index].info == dictWord) {
        // word in first link, spelled correctly
        spellCheck = 0;
    }
    else if(table[index].info != ""){
        // traverse chain to see if value is in table
        Node<string> *current = table[index].next;
        while(current != nullptr) {
            if(current->info == dictWord){
                // word found in chain
                spellCheck = 0;
                break;
            }
            current = current->next;
        }
    }
    // else table[index].info == "", word is not in hash table so it is spelled incorrectly

    return spellCheck;

}

HashTableChain::~HashTableChain() {
//    for(unsigned int i=0; i < size; i++){
//        Node<string> *current = &table[i];
//        delete current;
//    }
    delete [] table;
    table = nullptr;
}


#endif //P2_HASHTABLECHAINING_H
