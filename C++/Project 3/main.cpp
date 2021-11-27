/*
  *  main.cpp
  *
  *  COSC 052 Fall 2021
  *  Project #3
  *
  *  Due on: OCT 28, 2021
  *  Author: Aidan Pizzo  app59
  *
  *
  *  In accordance with the class policies and Georgetown's
  *  Honor Code, I certify that, with the exception of the
  *  class resources and those items noted below, I have neither
  *  given nor received any assistance on this project.
  *
  *  References not otherwise commented within the program source code.
  *  Note that you should not mention any help from the TAs, the professor,
  *  or any code taken from the class textbooks.
  */

#include "main.h"

int main(int argc, const char * argv[])
{
    try
    {
        string errMsg1 = "Must pass input file name and complete path as command line argument\n";
        if (argc < 2) // if command line arguments are invalid, throw exception
        {
            throw invalid_argument(errMsg1);
        }

        // create character list, populate using push back and push front
        LL<char> theList;
        cout << "Populating the character linked list..." << endl;
        theList.push_back('A');
        theList.push_back('I');
        theList.push_back('D');
        theList.push_back('A');
        theList.push_back('N');
        theList.push_front('!');
        theList.push_back('!');
        cout << theList;
        theList.pop_front();
        theList.pop_back();

        // create second char list, use overloaded operator, test insert function
        cout << "Creating second char list..." << endl;
        LL<char> theList2 = theList;
        theList2.insert(3, 'E');
        cout << theList2;

        // create third char list using copy constructor, empty list
        cout << "Creating third char list ..." << endl;
        LL<char> theList3(theList2);
        cout << theList3 << endl;
        theList3.clear();
        cout << "The cleared list: ";
        cout << theList3 << endl;

        // test front, back and search methods
        cout << "Testing back function: " << theList.back() << endl;
        cout << "Testing front function: " << theList.front() << endl;
        cout << "Searching for an E..." << endl;
        unsigned found_e = theList2.linearSearch('E');
        cout << "Found at index " << found_e << endl << endl;

        // create int list and test searching and sorting methods
        LL<int> intList;
        cout << "Populating the integer list..." << endl;
        intList.push_back(4);
        intList.push_back(2);
        intList.push_back(5);
        intList.push_back(1);
        intList.push_back(3);
        cout << "Here is the int list: " << endl << intList << endl;
        cout << "Sorting..." << endl;
        // intList.selectionSort();
        // intList.bubbleSort();
        intList.insertionSort();
        cout << "Sorted List: " << endl;
        cout << intList;
        cout << "Searching for a 4..." << endl;
        unsigned found_int = intList.binarySearch(4);
        cout << "Found at index " << found_int << endl;


        /*
        LL<Date> dateList;
        string fileName = string(argv[1]); // take fileName from second command line argument
        ifstream inFile;
        inFile.open( fileName.c_str()); // open file

        string garb;
        getline(inFile, garb);
        Date today;
        inFile >> today;
        cout << today <<endl; //WHY IS IT IN A FAILED STATE WHEN I TRY TO RUN BELOW CODE

        while (inFile)
        { // populate linked list with Dates
            Date addThis;

            inFile >> addThis;
            dateList.push_back(addThis);
        }
        cout << dateList;
        */

    }
    catch (no_such_object &e)
    {
        cout << "Caught no_such_object exception in function main.\n";
        cout << e.what();
        cout << endl;
    }
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
    catch (...)
    {
        cout << "Unknown exception caught in function main." << endl;
    }

   return 0;
}
