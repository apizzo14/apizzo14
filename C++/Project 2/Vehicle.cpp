/*
* Vehicle.cpp
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

#include "Vehicle.h"



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **               class Vehicle implementation code                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

Vehicle::Vehicle()
{ // set values to defaul
    this->setID(DEFAULT_ID);
    this->setName(DEFAULT_NAME);
    Date setTheDate; // create default date to then pass to set
    this->setInspectionDate(setTheDate);
    this->setStatus(DEFAULT_STATUS);
}


Vehicle::~Vehicle()
{
    // nothing to do here
}


Vehicle::Vehicle(string id, string name, Date inspectionDate, char status)
{ // set values to those passed by parameters
    this->setID(id);
    this->setName(name);
    this->setInspectionDate(inspectionDate);
    this->setStatus(status);
}


void Vehicle::print(ostream &os) const
{
    std::string errOutStream = "ERROR: in print function of the IncidentLog class<<\n";
    errOutStream += "the output stream is in a failed state, no processing can take place...\n";

    // if output is in a failed state, throw an invalid argument exception
    if (!os)
    {
        throw std::invalid_argument(errOutStream);
    }

    // output information
    os << "Vehicle ID: " << id << endl;
    os << "Make/Model: " << name << endl;
    os << "Last Inspection: " << inspectionDate << endl;

    // get full status
    string outputStatus;
    if( this-> status == 'm')
        outputStatus = "In Maintenance";
    if( this->status == 's')
        outputStatus = "In Service";
    if( this-> status == 'a')
        outputStatus = "Available";
    // print status
    os << "Current Status: " << outputStatus << endl;
} // END function print for Vehicle class


void Vehicle::read(istream &in)
{
    std::string errInStream = "ERROR: in IncidentLog class read function\n";
    errInStream += "the input stream is in a failed state, no processing can take place...\n";
    if (!in)
    { // if input stream is in failed state, throw exception
        throw std::invalid_argument(errInStream);
    }

    // input stream success, load the data
    // instantiate local variables
    string inId;
    string inName;
    Date inDate;
    char inStatus;

    // read in values
    in >> inId;
    inName = readDoubleQuotedString(in);
    in >> inDate >> inStatus;

    //set values
    this->setID(inId);
    this->setName( inName);
    this->setInspectionDate( inDate);
    this->setStatus(inStatus);
} // END function read for Vehicle class


void Vehicle::setID(string id)
{
    bool badId = false;
    string errMsg;

    if ( id.size() != 17 ) //ID must be 17 characters
    {
        badId = true;
        errMsg = "Invalid ID. The id must be a character of length 17.";
    }
    if (id[0] != 'i' &&
        id[0] != 'p' &&
        id[0] != 'c' ) // ID must begin with i, p, or c
    {
        badId = true;
        errMsg = "Invalid ID. The first character must be a valid vehicle type: i, p, or c.";
    }
    for ( unsigned int i=0; i < id.length(); i++)
    {
        if ( isdigit(id[i]) == false &&  isalpha(id[i]) == false)
        {
            badId = true;
            errMsg = "Invalid ID. The string must be alphanumeric.";
        }
    }

    if (badId)
    { // if any parameter fails validation, throw exception
        throw bad_vehicle_code(errMsg);
    }

    // parameters have passed validation, set values
    this->id = id;
} // END function setID for Vehicle class


void Vehicle::setName(string name)
{
    this->name = name;
}


void Vehicle::setInspectionDate(Date iDate) {
    this->inspectionDate.setDate(iDate);
}


void Vehicle::setStatus(char status) {
    //validate parameter
    if (status != 'm' && status != 's' && status != 'a') // status must be m, s, or a
    { // if invalid, throw exception
        string errMsg = "Invalid status. Must be m, s, or a.\n";
        throw invalid_argument(errMsg);
    }

    // parameter is valid, set status
    this->status = status;
}





/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **              class Individual implementation code                      **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

Individual::Individual() : Vehicle() {
    // base class constructor called, no additional code required
}

Individual::Individual(string id, string name, Date inspectionDate, char status)
                        : Vehicle(id, name, inspectionDate, status)
{
    //base class constructor called, no additional code required
}




/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                class Passenger implementation code                     **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

Passenger::Passenger(unsigned short c) : Vehicle()
{ // call base class constructor, set capacity
    this->setCapacity( c );
}

Passenger::Passenger(string id, string name, Date inspectionDate, char status, unsigned short cap)
                        : Vehicle(id, name, inspectionDate, status)
{ // call base class constructor, set capacity
    this->setCapacity( cap );
}

void Passenger::print(ostream &os) const
{
    // call print from Vehicle class
    Vehicle::print(os);

    //output capacity
    os << "Max. Passengers: " << capacity << endl;
}

void Passenger::read(istream &in)
{
    Vehicle::read(in);

    int inCapacity;
    //read in capacity
    in >> inCapacity;
    //set capacity
    this->setCapacity(inCapacity);
    // cout << "The Passenger object has been read.\n";
}

void Passenger::setCapacity(unsigned short cap)
{
    if ( cap > MAX_PASSENGER_CAPACITY || cap < MIN_PASSENGER_CAPACITY )
    { // if invalid capacity, throw exception
        string errMsg = "Invalid passenger capacity, must be in [0, 250].";
        throw too_many_passengers(errMsg);
    }

    // capacity is valid, set value
    this->capacity = cap;
}



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Cargo implementation code                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

Cargo::Cargo(double c) : Vehicle()
{ // call base class constructor, set capacity
    this->setCapacity(c);
}

Cargo::Cargo(string id, string name, Date inspectionDate, char status, double cap)
                : Vehicle(id, name, inspectionDate, status)
{ // call base class constructor, set capacity
    this->setCapacity(cap);
}

void Cargo::print(ostream &os) const
{ // call print from Vehicle class
    Vehicle::print(os);

    // output cargo cap
    os << "Max. Payload: " << capacity << endl;
}

void Cargo::read(istream &in)
{
    Vehicle::read(in);

    double inCapacity;
    //read in capacity
    in >> inCapacity;
    //set capacity
    this->setCapacity(inCapacity);
    // cout << "The Cargo object has been read.\n";
}

void Cargo::setCapacity(double cap)
{
    if ( cap > MAX_CARGO_CAPACITY || cap < MIN_CARGO_CAPACITY )
    { // if invalid capacity, throw exception
        string errMsg = "Invalid cargo capacity, must be in [0.0, 25.0].";
        throw too_much_cargo(errMsg);
    }

    // capacity is valid, set value
    this->capacity = cap;
}
