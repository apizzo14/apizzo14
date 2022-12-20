/*
 * Aidan Pizzo
 * Data Structures
 * Project 3(a)
 *
 * This project will read in a series of integers and store them in a Binary Search Tree. Then more
 * integers will be processed and used to search the constructed BST. Finally, more integers can be
 * read in and deleted from the tree
*/

#include "BST.h"
#include "Node.h"
#include "SplayTree.h"
#include <fstream>
#include <chrono>
using namespace std;

int main(int argc, const char * argv[]) {
    try {

        if (argc < 2) // if command line arguments are invalid
        {
            cout << "Must pass an input file on command line\n";
            return 0;
        }


        /**********************************************
         *                     BST                    *
         **********************************************/

        // read file name from command line
        string inputFile = string(argv[1]);

        ifstream inFile;
        inFile.open(inputFile.c_str());
        if (!inFile) // if file doesn't open, throw exception
        {
            cout << "File failed to open, check path and name: \n";
            cout << inputFile << endl;
            throw logic_error("File failed to open");
        }

        // record start time
        auto BSTTimeStart = chrono::steady_clock::now();
        // create BST
        BST BSTree = BST();

        int input = 0;
        cout << "Inserting data into the Binary Search Tree...\n";
        while(inFile >> input){
            // read from input file and insert into BST
            BSTree.insert(BSTree.root, input);
//            cout << "Inserting " << input << endl;
        }

        // print tree
        cout << "Here is the tree:\n";
        BSTree.displayTree(BSTree.root);
        cout << endl;

        // read in $ from input file
        char dollar;
        inFile.clear();
        inFile >> dollar;

        cout << "Searching for data in the BST...\n";
        while(inFile >> input){
            // read from input file and search
            BSTree.search(BSTree.root, input);
        }

        // read in $ from input file
        inFile.clear();
        inFile >> dollar;

        cout << "Removing items of the BST...\n";
        while(inFile >> input){
            // read from input file and remove items from tree
//            cout << "Removing " << input << endl;
            BSTree.remove(BSTree.root, input);
        }
        inFile.close();

        cout << "Here is the final Binary Search Tree:\n";
        BSTree.displayTree(BSTree.root);
        cout << endl << endl;
//        cout << "Deallocating...\n";
//        BSTree.deallocateTree(BSTree.root);
//        cout << "Tree:\n";
//        BSTree.displayTree(BSTree.root);

        //record end time
        auto BSTTimeEnd = std::chrono::steady_clock::now();

        // calculate elapsed time, convert to nanoseconds
        double BSTelapsed_time = chrono::duration_cast<chrono::nanoseconds>(BSTTimeEnd - BSTTimeStart).count();


        /**********************************************
         *                Splay Tree                  *
         **********************************************/

        inFile.open(inputFile.c_str());
        if (!inFile) // if file doesn't open, throw exception
        {
            cout << "File failed to open, check path and name: \n";
            cout << inputFile << endl;
            throw logic_error("File failed to open");
        }

        // record start time
        auto splayTreeTimeStart = chrono::steady_clock::now();
        // create BST
        SplayTree splayTree = SplayTree();

        cout << "Inserting data into the Splay Tree...\n";
        while(inFile >> input){
            // read from input file and insert into BST
//            cout << "Inserting " << input << endl;
            splayTree.insert(splayTree.root, input);
//            splayTree.displayTree(splayTree.root);
//            cout << endl;
        }

        // print tree
        cout << "Here is the Splay Tree:\n";
        splayTree.displayTree(splayTree.root);
        cout << endl;

        // read in $ from input file
        inFile.clear();
        inFile >> dollar;

        cout << "Searching for data in the Splay Tree...\n";
        while(inFile >> input){
            // read from input file and search
            splayTree.search(splayTree.root, input);
        }

        // read in $ from input file
        inFile.clear();
        inFile >> dollar;

        cout << "Removing items from the Splay Tree...\n";
        while(inFile >> input){
            // read from input file and remove items from tree
//            cout << "Removing " << input << endl;
            splayTree.remove(splayTree.root, input);
        }
        inFile.close();

        cout << "Here is the final Splay Tree:\n";
        splayTree.displayTree(splayTree.root);
        cout << endl << endl;

        //record end time
        auto splayTreeTimeEnd = std::chrono::steady_clock::now();

        // calculate elapsed time, convert to nanoseconds
        double splayTreeElapsed_time = chrono::duration_cast<chrono::nanoseconds>(splayTreeTimeEnd - splayTreeTimeStart).count();

        cout << "Total time taken \n";
        cout << "BST:           " << BSTelapsed_time << " nanoseconds\n";
        cout << "Splay Tree:    " << splayTreeElapsed_time << " nanoseconds\n\n";
        cout << "Traversal Count: \n";
        cout << "BST:           " << BSTree.getTraversalCount() << endl;
        cout << "Splay Tree:    " << splayTree.getTraversalCount() << endl << endl;

        if(BSTelapsed_time < splayTreeElapsed_time){
            cout << "The Binary Search Tree was faster.\n";
        }
        else{
            cout << "The Splay Tree was faster.\n";
        }
        if(BSTree.getTraversalCount() < splayTree.getTraversalCount()){
            cout << "The Binary Search Tree required less traversals.\n";
        }
        else{
            cout << "The Splay Tree required less traversals.\n";
        }


    } // END try block
    catch (out_of_range &e)
    {
        cout << "Caught out_of_range exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (invalid_argument &e)
    {
        cout << "Caught invalid_argument exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (logic_error &e)
    {
        cout << "Caught logic_error exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (bad_alloc &e)
    {
        cout << "Caught bad_alloc exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
    catch (...)
    {
        cout << "Unknown exception caught in function main." << endl;
    }

    return 0;

} // END main function
