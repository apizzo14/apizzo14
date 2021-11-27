/*
* main.cpp
*
* COSC 052 Fall 2021 * Project #2
*
* Due on: OCT 7, 2021
* Author: Aidan Pizzo app59
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project. *
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks. */

#include "main.h"

int main( int argc, const char * argv[])
{
    string errMsg1 = "Must pass input file name and complete path as command line argument\n";
    if (argc < 2) // if command line arguments are invalid, throw exception
    {
        throw invalid_argument(errMsg1);
    }

    VehicleLog allVehicles;
    string fileName = "";

    try
    {
        fileName = string(argv[1]); // take fileName from second command line argument
        allVehicles.read(fileName.c_str()); //read file, load data

        //print data
        cout << "Here is the loaded data: " << endl << endl;
        allVehicles.print();
        cout << endl << endl;
        cout << "Size: " << allVehicles.size() << endl;
        cout << "Total passenger capacity: " << allVehicles.getTotalPassengerCapacity() << endl;
        cout << "Total cargo capacity: " << allVehicles.getTotalCargoCapacity() << endl;

    } // END try block in main

    // catch blocks
    catch ( bad_vehicle_code &e)
    {
        cout << "Caught bad_vehicle_code exception in function main.\n";
        cout << e.what() << endl;
    }
    catch ( too_much_cargo &e)
    {
        cout << "Caught too_much_cargo exception in function main.\n";
        cout << e.what() << endl;
    }
    catch ( too_many_passengers &e)
    {
        cout << "Caught too_many_passengers exception in function main.\n";
        cout << e.what() << endl;
    }
    catch ( invalid_argument &e)
    {
        cout << "Caught invalid_argument exception in function main.\n";
        cout << e.what() << endl;
    }
    catch ( logic_error &e)
    {
        cout << "Caught logic_error exception in function main\n";
        cout << e.what() << endl;
    }
    catch ( ... )
    {
        cout << "Caught unknown exception in function main." << endl;
    }

    return 0;
} // END main function
