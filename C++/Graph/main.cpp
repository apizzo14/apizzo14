/*
 * Aidan Pizzo
 * Data Structures
 * Project 4
 *
 * This project will create an adjacency list graph after reading in vertices and edges from an
 * input file. Also in the input file is a line with a start vertex and end vertex, and this project will
 * also find the shortest path in the graph between the two using Dijkstra's algorithm, implemented with a
 * priority queue.
*/

#include "Graph.h"
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

        string startVertex, endVertex;

        // record start time
        auto timeStart = chrono::steady_clock::now();

        inFile >> startVertex >> endVertex;
//        cout << "Path goes " << startVertex << " " << endVertex << endl;

        // read in $ from input file
        char dollar;
        inFile.clear();
        inFile >> dollar;

        adjacencyList graph = adjacencyList();

        string tempStart, tempEnd;
        int tempCost;
        while(inFile >> tempStart){
            inFile >> tempEnd >> tempCost;
//            cout << tempStart << " " << tempEnd << " " << tempCost << endl;
            graph.addNode(tempStart, tempEnd, tempCost);
        }

//        graph.printGraph(); cout << endl;
//        cout << graph.numLists << endl;
//        cout << "SFO Index: " << graph.getIndex("SFO") << endl;

        cout << "Shortest Path: ";
        int pathCost = graph.getShortestPath(startVertex,endVertex);
        cout << endl;
        cout << "Cost: " << pathCost << endl;

        //record end time
        auto timeEnd = std::chrono::steady_clock::now();

        // calculate elapsed time, convert to nanoseconds
        double elapsed_time = chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();

        cout << "Time required: " << elapsed_time << " nanoseconds" << endl;


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

