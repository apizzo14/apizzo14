#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "MTFList.cpp"
#include "orderedList.cpp"

using namespace std;

int main(int argc, const char * argv[])
{
    if (argc < 2) // if command line arguments are invalid
    {
        cout << "Must pass an input file as command line argument\n";
        return 0;
    }

    string fileName = string(argv[1]); // take fileName from second command line argument
    ifstream inFile;
    inFile.open( fileName.c_str()); // open file

    if (!inFile) // if file doesn't open, throw exception
    {
        cout << "File failed to open, check path and name: \n";
        cout << fileName << endl;
        throw logic_error("File failed to open");
    }


    int length = 0,
    numQueries = 0,
    tempInt = 0,
    totalMoveListTraverse = 0,
    totalOListTraverse = 0;
    string garb = "";
    double totalMoveListTime = 0,
    totalOListTime = 0;

    // read in length of list
    inFile >> length;

    // initialize list objects
    MTFList<int> MoveList = MTFList<int>();
    orderedList<int> OList = orderedList<int>(length);

    // populate lists with integers in input file
    for (int i=0; i < length; i++){
        inFile >> tempInt;
        MoveList.add(tempInt);
//        cout << "First element: " << MoveList.header->info << endl;
        OList.add(tempInt, i);
//        getline(inFile, garb);
    }
//        cout << "First few elements of MoveList: " << MoveList.header->info << " " << MoveList.header->next->info
//        << " " << MoveList.header->next->next->info << endl;
//    cout << "First few elements of OList: " << OList.info[0] << " " << OList.info[1] << " " << OList.info[2] << endl;


    // read in number of queries
    inFile >> numQueries;

    // query lists
    for (int i=0; i < numQueries; i++){
        int lookingFor = 0;
        inFile >> lookingFor;
//        cout << "Looking for " << lookingFor << endl;

        MoveList.search(lookingFor, totalMoveListTraverse, totalMoveListTime);
//        cout << "First few elements of MoveList: " << MoveList.header->info << " " << MoveList.header->next->info
//        << " " << MoveList.header->next->next->info << endl << endl;

        OList.search(lookingFor, totalOListTraverse, totalOListTime);

    } // END traversing queries

    inFile.close();

    cout << "MTFList Traversal Count: " << totalMoveListTraverse << endl;
    cout << "orderedList Traversal Count: " << totalOListTraverse << endl << endl;
    cout << "MTFList time: " << totalMoveListTime << " nanoseconds" << endl;
    cout << "orderedList time: " << totalOListTime << " nanoseconds" << endl << endl;

    if(totalMoveListTime < totalOListTime){
        cout << "MTFList is faster for this data.\n";
    }
    else{
        cout << "orderedList is faster for this data.\n";
    }

    return 0;
}
