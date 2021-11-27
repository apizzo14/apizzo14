/*
* VehicleLog.cpp
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

#include "VehicleLog.h"

/****************************************************************************
 *                                                                          *
 *                     class VehicleLog implementation                      *
 *                                                                          *
 ****************************************************************************/

VehicleLog::VehicleLog()
{
    //nothing to do here
}

int VehicleLog::getTotalPassengerCapacity() const
{
    Passenger *ptr;
    int totalPassengerCap = 0;

    ptr = NULL;
    for (unsigned i = 0; i < vehicles.size(); i++)
    {
        //calculate passenger capacity
        ptr = dynamic_cast<Passenger*>( vehicles.at(i)); // dynamic cast to Passenger

        if ( ptr ) // dynamic cast is successful, now points to all Passenger objects
        {
            totalPassengerCap += ptr->getCapacity();

        }
    }
    return totalPassengerCap;
}// END function getTotalPassengerCapacity for VehicleLog class


double VehicleLog::getTotalCargoCapacity() const
{
    Cargo *ptr;
    double totalCargoCap = 0;

    ptr = NULL;
    for (unsigned i = 0; i < vehicles.size(); i++)
    {
        //calculate passenger capacity
        ptr = dynamic_cast<Cargo *>( vehicles.at(i)); // dynamic cast to Cargo

        if (ptr) // dynamic cast is successful, now points to all Cargo objects
        {
            totalCargoCap += ptr->getCapacity();

        }
    }
    return totalCargoCap;
} // END function getTotalCargoCapacity for VehicleLog class


void VehicleLog::print(ostream &os) const {
    std::string errOutStream = "ERROR: in print function of the IncidentLog class\n";
    errOutStream += "the output stream is in a failed state, no processing can take place...\n";

    // if output is in a failed state, throw an invalid argument exception
    if (!os) {
        throw std::invalid_argument(errOutStream);
    }

    for (unsigned int i = 0; i < vehicles.size(); i++)
    { // run through vector, print information for each
        int count = i+1;
        cout << "Vehicle " << count << endl;
        this->vehicles.at(i)->print();
        cout << endl;
    }
} // END function print for VehicleLog class

void VehicleLog::read(string fileName)
{
    ifstream inFile;
    inFile.open( fileName.c_str()); // open file

    if (!inFile) // if file doesn't open, throw exception
    {
        cout << "File failed to open, check path and name: \n";
        cout << fileName << endl;
        throw invalid_argument("File failed to open");
    }
    while( inFile )
    {
        char whichVehicle;
        string garb;
        Passenger *ptrPas;
        Individual *ptrInd;
        Cargo *ptrCgo;

        try
        {
            // read in ID to see which type of vehicle, then putback to begin at start of line
            inFile >> whichVehicle;
            inFile.putback(whichVehicle);

            if (whichVehicle == 'p') {
                // allocate mem for a new pointer, read info into Passenger object,
                // add that object to the vector
                ptrPas = new Passenger;
                ptrPas->read(inFile);
                vehicles.push_back(ptrPas);
            } else if (whichVehicle == 'i') {
                // allocate mem for a new pointer, read info into Individual object,
                // add that object to the vector
                ptrInd = new Individual;
                ptrInd->read(inFile);
                vehicles.push_back(ptrInd);
            } else if (whichVehicle == 'c') {
                // allocate mem for a new pointer, read info into Cargo object,
                // add that object to the vector
                ptrCgo = new Cargo;
                ptrCgo->read(inFile);
                vehicles.push_back(ptrCgo);
            } else
            { // invalid character at beginning of line
                std::string errOutStream = "Invalid ID while reading the input file.\n";
                errOutStream += "The ID must begin with i, p, or c.\n";
                errOutStream += "Skipping this line...\n";
                //read the rest of the line
                getline(inFile, garb);
                throw invalid_argument(errOutStream);
            }
        }

        catch (invalid_argument &e)
        {
            cout << "Invalid argument error caught in read method of VehicleLog class\n";
            cout << e.what() << endl;
        }

    }
    inFile.close();
} // END function read for VehicleLog class

unsigned long VehicleLog::size() const
{
    return vehicles.size();
}

Vehicle &VehicleLog::at(unsigned long ndx)
{
    return *this->vehicles[ndx];
}

VehicleLog::~VehicleLog()
{
    for ( unsigned int i; i < this->size(); i++)
    {
        delete this->vehicles[i];
    }
}
