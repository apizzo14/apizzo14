/*
* Exceptions.cpp
*
* COSC 052 Fall 2021 * Project #3
*
* Due on: OCT 28, 2021
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

#include "Exceptions.h"


/****************************************************************************
 *                                                                          *
 *                  class bad_vehicle_code implementation                   *
 *                                                                          *
 ****************************************************************************/

bad_vehicle_code::bad_vehicle_code(string msg) : invalid_argument( msg )
{
    // nothing to do here
}


/****************************************************************************
 *                                                                          *
 *                  class no_such_object implementation                     *
 *                                                                          *
 ****************************************************************************/

no_such_object::no_such_object(string msg) : logic_error( msg )
{
    // nothing to do here
}
