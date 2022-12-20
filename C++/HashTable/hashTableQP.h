/*
 * This class is a hash table that uses the quadratic probing method to handle collisions
 *
 * Created by Aidan Pizzo
 */

#ifndef P2_HASHTABLEQP_H
#define P2_HASHTABLEQP_H

#include <chrono>
#include <string>
#include "Node.h"
#include <chrono>
#include <string>
#include <iostream>

using namespace std;

class HashTableQP
{
private:
    int size;
    string *table;

public:
    // constructor
    HashTableQP(int);

    // destructor
    ~HashTableQP();

    // insert word into hash table dict
    void insert(string);

    // hash function returns index of word
    int hashFunction(string);

    // print for testing
    void printTable();

    // perform spell check
    int spellCheck(string);

};

HashTableQP::HashTableQP(int tableSize) {
    size = tableSize;
    table = new string[size];
    for(int i=0; i < size; i++){
        table[i] = "";
    }
}

void HashTableQP::insert(string DictWord) {
//    cout << "Entering insert method\n";

    // get index of hash table using hash function function
    int index = hashFunction(DictWord);

    // if index is empty (no collision) add dict info
    if(table[index] == ""){
        // no need to traverse
    }
    else{ // collision, add dict info to next open link in chain
//        cout << "Collision!\n";
        int increment = 1;
        while(table[index] != ""){
            index += (increment * increment);
            index = index % size;
            increment++;
        }
//        cout << "Ending traversal\n";
        // add new node with dictionary info
    } // END else condition: linked list is not empty

    // index is empty, add word to hash table
    table[index] = DictWord;
}

int HashTableQP::hashFunction(string dictWord) {
    unsigned int hashValue = 0;
    for(char ch : dictWord)
        hashValue = 37 * hashValue + ch;
    return hashValue % size;
}

void HashTableQP::printTable() {
    for(int i=0; i < size; i++) {
        cout << i << " --> " << table[i];
        cout << endl;
    } // END for loop traversing string array
}

int HashTableQP::spellCheck(string dictWord) {
    int spellCheck = 1;
    int index = hashFunction(dictWord);
    if(table[index] == dictWord){
        // word is in table, spelled correctly
        spellCheck = 0;
    }
    else if(table[index] != ""){
        int increment = 1;
        // quadratic probe to see if word is in table
        while(table[index] != ""){
            index += increment;
            if(table[index] == dictWord) {
                spellCheck = 0;
                break;
            }
        }
    }
//     else table[index] == "", spellCheck is 1 to indicate misspelled word

    return spellCheck;

}

HashTableQP::~HashTableQP() {
    // nothing to do here
}

#endif //P2_HASHTABLEQP_H
