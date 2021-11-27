/*
* Exceptions.cpp
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

#include "Exceptions.h"


/****************************************************************************
 *                                                                          *
 *                  class bad_vehicle_code implementation                   *
 *                                                                          *
 ****************************************************************************/

bad_vehicle_code::bad_vehicle_code( std::string msg) : invalid_argument( msg )
{
   //nothing to do here
}



/****************************************************************************
 *                                                                          *
 *               class too_many_passengers implementation                   *
 *                                                                          *
 ****************************************************************************/

too_many_passengers::too_many_passengers( std::string msg) : invalid_argument( msg )
{
    // nothing to do here
}



/****************************************************************************
 *                                                                          *
 *                      class too_much_cargo declaration                    *
 *                                                                          *
 ****************************************************************************/

too_much_cargo::too_much_cargo( std::string msg) : invalid_argument( msg)
{
    // nothing to do here
}
