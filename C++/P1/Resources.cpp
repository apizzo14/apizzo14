/*
  *  Resources.cpp
  *
  *  COSC 052 Fall 2021
  *  Project #1
  *
  *  Due on: SEP 16, 2021
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


#include "Resources.h"


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Time implementation code                         **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Fall 2021 to use in                        **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



/****************************************************************************
 *                    Time class default constructor                        *
 ****************************************************************************/

/**
 * <P>Constructor with parameters, also default constructor since all
 * parameters have default values.</P>
 * <P>Sets the hh and mm data members to values passed to parameters.</P>
 * <P>Uses 24-hour format so 24:00 is midnight
 * 12:00 is noon, 13:00 is 1:00 pm, etc.</P>
 * <P>Note that 00:00 is also accepted as midnight but will be converted to 24:00</P>
 * <P>In addition to the range of valid values below, if the hour value is 24, then
 * the minute value must be 00.</P>
 * <P>Shall call the setTime method with integer parameters
 * to perform validation testing and actually initialize hh and mm
 * if all values pass validation.</P>
 *
 * @param  hour an int value in [0, 24]
 * @param  minute an int value in [0, 59] (must be 0 if hour is 24)
 * @throws invalid_argument if any parameter fails validation
 */

Time::Time(int hour, int minute)
{
#ifdef DEBUG_DATE
    std::cout << "Entered constructor Time::Time(int, int)" << std::endl;
#endif

    // call method setTime where data validation will be accomplished

    setTime(hour, minute);

#ifdef DEBUG_DATE
    std::cout << "Exiting constructor Time::Time(int, int)" << std::endl;
#endif

} //END constructor with parameters for Time class



/****************************************************************************
 *                  Time class member function setTime                      *
 ****************************************************************************/

/**
 * <P>Time class member function to set the hh and mm data members to
 * to the values passed in to the two integer parameters.</P>
 * <P>NOTE: see default constructor for valid values.</P>
 *
 * @param  hour an int value
 * @param  minute an int value
 * @throws invalid_argument if any parameter fails validation
 */

void Time::setTime(int hour, int minute)
{
    // use string stream to generate message with heterogeneous data types
    // see code in if(badArguments) block
    std::ostringstream errStrm;

    // set data members to default values, if values passed
    // in to the parameters pass validation, then the
    // data members will be updated
    hh = MIN_HOUR;
    mm = MIN_MINUTE;

    bool badArguments = false;

    if ( hour < MIN_HOUR || minute < MIN_MINUTE || hour > MAX_HOUR || minute > MAX_MINUTE )
    {
        // one on more of the values passed in are not valid
        badArguments = true;
    }
    else if ( hour == MAX_HOUR && minute != 0 )
    {
        // if the value passed for hour is 24, then the only valid value for minutes is 0
        badArguments = true;
    }

    // accept 00:00 as midnight, but silently convert to 24:00
    if ( hour == 0 && minute == 0)
    {
        hour = 24;
    }

    if (badArguments)
    {
        // one or more parameters are not valid, throw an exception
        // note that we do not need a try block to throw the exception since
        // we do not plan to handle the exception within Time::setTime
        // control will immediately return to the calling function

        errStrm << "ERROR: in method Time::setTime( " << hour << ", " << minute << " )\n";
        errStrm << "hour set to MIN_HOUR (" << MIN_HOUR << "), ";
        errStrm << "minute set to MIN_MINUTE (" << MIN_MINUTE << ")\n";
        std::string errTime = errStrm.str();

        std::invalid_argument e(errTime);
        throw e;
    }

    // both parameters are valid, update object's data members

    hh = hour;
    mm = minute;

} //END member function Time::setTime



/****************************************************************************
 *                 Time class stream extraction operator                    *
 ****************************************************************************/

/**
 * <P>friend function, overloaded stream extraction operator, Time class</P>
 * <P>Extracts values for a Time object's data members
 * from the input stream.</P>
 * <P>The input format is assumed to hh:mm, be aware that
 * the minute will always be a 2-digit number, right padded with
 * a 0 if necessary, hour values could be either 2-digit or 1-digit numbers.</P>
 * <P>After the values are extracted, the modified input stream is returned.</P>
 * <P>Shall call the setTime method with integer parameters
 * to perform validation testing and actually update hh and mm
 * if all values pass validation.</P>
 * <P>NOTE: see default constructor for valid values.</P>
 *
 * @param  in  the input stream for extraction
 * @param  t  the Time object for storing the extracted information
 * @return  the modified input stream
 * @throws invalid_argument if the input stream is initially in a failed state
 * @throws invalid_argument (via Time::setTime method) if any parameter fails validation
 *
 */

std::istream& operator>>(std::istream &in, Time &t)
{
    // input format is expected to be hh:mm
    // examples:
    // 24:00 for midnight
    // 12:00 for noon
    // 2:45 45 minutes past 2 am
    // 14:45 45 minutes past 2 pm
    // etc.

    char ch;
    int hour = -1;
    int minute = -1;

    // if stream is originally in a failed throw an exception
    // this is thrown outside of the try block so it will not be
    // handled locally, but will immediately pass control back
    // to the calling function

    std::string errInStream = "ERROR: in Time class overloaded operator>>\n";
    errInStream += "the input stream is in a failed state, no processing can take place...\n";
    if (!in)
    {
        throw std::invalid_argument(errInStream);
    }

    try
    {
        bool streamFailed = false;

        in >> hour; //extract the hours and store them in local variable
        if (!in) { streamFailed = true; }

        in >> ch; //extract and discard the dilimiting character
        if (!in) { streamFailed = true; }

        in >> minute; //extract the minutes and store them in local variable
        if (!in) { streamFailed = true; }

        // if stream entered a failed state while extracting values
        // throw an exception
        // this is thrown inside of the try block so it will be
        // handled locally
        // in this case, local processing does not rethrow
        // this technique assumes that the point in the program from which
        // the overloaded stream extraction operator was called will test
        // for the stream being in a failed state after the function
        // call and take appropriate action

        if(streamFailed)
        {
            std::string errInStream = "WARNING: in Time class overloaded operator>>\n";
            errInStream += "the input stream is in a failed state, ";
            errInStream += "possible attempt to read past end of file, ";
            errInStream += "time object data members not updated ...\n";
            throw std::runtime_error(errInStream);
        }

        t.setTime(hour, minute); // call setTime method where validation will take place
    }
    catch (std::runtime_error &e)
    {
        std::cout << "WARNING: ";
        std::cout << "caught runtime_error exception in Time class overloaded operator>>\n";
        std::cout << e.what() << endl;
        // allow processing to continue, do not re-throw
    }
    catch (std::invalid_argument &e)
    {
        std::cout << "ERROR: ";
        std::cout << "caught invalid_argument exception in Time class overloaded operator>>\n";
        std::cout << e.what() << endl;
        // do not allow processing to continue, re-throw
        throw;
    }
    catch (...)
    {
        std::cout << "ERROR: unknown exception caught in Time class overloaded operator>>\n";
        throw;
    }

    return in;

} //END overloaded stream extraction operator for Time class



/****************************************************************************
 *                 Time class stream insertion operator                     *
 ****************************************************************************/

/**
 * <P>friend function, overloaded stream insertion operator of Time class.</P>
 * <P>Inserts a Time object into the output stream
 * and returns the modified output stream.</P>
 * <P>The output format is the same as the input format expected
 * by the overloaded stream extraction operator: hh:mm, unlike
 * the stream extraction operator, the stream insertion operator
 * shall always output hours and minutes having 2-digits (use left
 * padding with a 0 for hours and minutes less than 10)</P>
 *
 * @param  os  the output stream for insertion
 * @param  t   the Time object for insertion
 * @return  the modified output stream
 * @throws invalid_argument if the output stream is initially in a failed state
 */

std::ostream& operator<<(std::ostream &os, const Time &t)
{

    std::string errOutStream = "ERROR: in Time class overloaded operator<<\n";
    errOutStream += "the output stream is in a failed state, no processing can take place...\n";
    if (!os)
    {
        throw std::invalid_argument(errOutStream);
    }

    // if the hour value of minute value is < 10, then pad on the left with a 0 character
    os << std::setfill('0');

    os << std::setw(2) << t.hh << ":";
    os << std::setw(2) << t.mm;

    // set the fill character back to a blank space to prevent really ugly output of other values
    os << std::setfill(' ');

    return os;

} //END overloaded stream insertion operator for Time class



/****************************************************************************
 *                     Time class assignment operator                       *
 ****************************************************************************/

/**
 * <P>Overloaded assignment operator.</P>
 * <P>Sets the hh amd mm data members to values of the corresponding
 * data members of the Time object passed in as a parameter.</P>
 * <P>Should test for self assignment (not an issue with this class, but
 * good habit nevertheless).</P>
 * <P>Should call the setTime method with integer parameters
 * to perform validation testing and actually update hh and mm
 * if all values pass validation.</P>
 * <P>NOTE: see default constructor for valid values.</P>
 *
 * @param  rhsObj a Time object
 * @throws invalid_argument (via setTime method) if any parameter fails validation
 */

Time Time::operator=(const Time &rhsObj)
{
    if (this != &rhsObj)
    {
        // not a self assignment, OK to proceed
        // call method setTime where validation will be accomplished

        setTime(rhsObj.hh, rhsObj.mm);
    }

    return *this;

} //END overloaded assignment operator for Time class



/****************************************************************************
 *                 Time class overloaded equality operator                  *
 ****************************************************************************/

/**
 * <P>Overloaded equality operator, Time class.</P>
 * <P>Returns true if the left side Time object is equal to the right side Time object.</P>
 *
 * @param  rhsObj a Time object
 * @return true if both objects have the same hour value and minute value, false otherwise
 *
 */

bool Time::operator==( const Time &rhsObj ) const
{
    return ( this->hh == rhsObj.hh && this->mm == rhsObj.mm );

} // END overloaded equality operator for Time class



/****************************************************************************
 *                Time class overloaded inequality operator                 *
 ****************************************************************************/

/**
 * <P>Overloaded inequality operator, Time class.</P>
 * <P>Returns true if the left side Time object is NOT equal to the right side Time object.</P>
 *
 * @param  rhsObj a Time object
 * @return true if objects have either different hour value or minute value, false otherwise
 *
 */

bool Time::operator!=( const Time &rhsObj ) const
{
    return !( *this == rhsObj );

} // END overloaded inequality operator for Time class



/****************************************************************************
 *               Time class overloaded greater than operator                *
 ****************************************************************************/

/**
 * <P>Overloaded greater than operator, Time class.</P>
 * <P>Returns true if the left side Time object is greater than the right side Time object.</P>
 *
 * @param  rhsObj a Time object
 * @return true if left side object is greater than the right side object, false otherwise
 *
 */

bool Time::operator>( const Time &rhsObj ) const
{
    bool answer = false;

    if ( this->hh > rhsObj.hh )
    {
        answer = true;
    }
    else if ( (this->hh == rhsObj.hh) && (this->mm > rhsObj.mm) )
    {
        answer = true;
    }

    return answer;

} // END overloaded greater than operator, Time class



/****************************************************************************
 *                 Time class overloaded less than operator                 *
 ****************************************************************************/

/**
 * <P>Overloaded less than operator, Time class.</P>
 * <P>Returns true if the left side Time object is less than the right side Time object.</P>
 *
 * @param  rhsObj a Time object
 * @return true if left side object is less than the right side object, false otherwise
 *
 */

bool Time::operator<( const Time &rhsObj ) const
{
    bool answer = false;

    if ( this->hh < rhsObj.hh )
    {
        answer = true;
    }
    else if ( (this->hh == rhsObj.hh) && (this->mm < rhsObj.mm) )
    {
        answer = true;
    }

    return answer;

} // END overloaded greater than operator, Time class


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Date implementation code                         **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



/****************************************************************************
 *                                                                          *
 *   Overloaded stream insertion and extraction operators for Date class    *
 *                                                                          *
 ****************************************************************************/

istream& operator>>(istream& in, Date& dt)
{
  int year = 0;
  int month = 0;
  int day = 0;
  char ch = 'a';
  //dt.setDate(MIN_YYYY, MIN_MM, MIN_DD); // initialize date object

  in >> year >> ch >> month >> ch >> day;

  std::string errInStream = "ERROR: in Date class overloaded operator>>\n";
  errInStream += "the input stream is in a failed state, no processing can take place...\n";
  if (!in)
  {
    throw std::invalid_argument(errInStream);
  }

  dt.setDate(year, month, day); //call function setDate to load private members

  return in;

} // END overloaded stream extraction operator for Date class


ostream& operator<<(std::ostream& out, const Date& dt)
{
  std::string errOutStream = "ERROR: in Date class overloaded operator<<\n";
  errOutStream += "the output stream is in a failed state, no processing can take place...\n";
  if (!out)
  {
      throw std::invalid_argument(errOutStream); // throw an invalid argument exception
  }

  // if the hour value of minute value is < 10, then pad on the left with a 0 character
  out << std::setfill('0');

  out << std::setw(2) << dt.yyyy << "/";
  out << std::setw(2) << dt.mm << "/";
  out << std::setw(2) << dt.dd;

  // set the fill character back to a blank space to prevent really ugly output of other values
  out << std::setfill(' ');

  return out;

} // END overloaded stream insertion operator for Date class


/****************************************************************************
 *                 Date class default and copy constructors                 *
 ****************************************************************************/

Date::Date(int year, int month, int day) //yyyy, mm, dd
{
  yyyy = year;
  mm = month;
  dd = day;
}

Date::Date(const Date& date) // IS THIS A DATE VARIABLE? OR A CONSTANT?
{
  this->setDate( date );
}


/****************************************************************************
 *                                                                          *
 *            class Date member function implementation code               *
 *                                                                          *
 ****************************************************************************/


void Date::setDate(int year, int month, int day)  //yyyy, mm, dd
{
  // use string stream to generate message with heterogeneous data types
  // see code in if(badArguments) block
  std::ostringstream errStrm;

  // set data members to default values, if values passed
  // in to the parameters pass validation, then the
  // data members will be updated
  yyyy = MIN_YYYY;
  mm = MIN_MM;
  dd = MIN_DD;

  if ( year < MIN_YYYY || year > MAX_YYYY || month < MIN_MM || month > MAX_MM ||
  day < MIN_DD || day > MAX_DD[month])
  {
    errStrm << "ERROR: in method Date::setDate( " << year << "/" << month << "/" << day << ")\n";
    errStrm << "Date is out of range.\n";
    errStrm << "Year set to MIN_YEAR (" << MIN_YYYY << "), ";
    errStrm << "month set to MIN_MONTH (" << MIN_MM << "), ";
    errStrm << "day set to MIN_DAY (" <<MIN_DD << ")\n";
    std::string errDate = errStrm.str();

    throw invalid_argument(errDate);
  } 

  // parameters are valid, update data members
  yyyy = year;
  mm = month;
  dd = day;

} // END default constructor for Date class


void Date::setDate(const Date& otherDate)
{
  this->yyyy = otherDate.yyyy;
  this->mm = otherDate.mm;
  this->dd = otherDate.dd;

} // END copy constructor for Date class


Date Date::operator=(const Date& rhs)
{
  if (this != &rhs)
  {
    this->setDate(rhs.getYear(), rhs.getMonth(), rhs.getDay());
  }

  return *this;

} // END overloaded assignment operator for Date class


int Date::getYear() const
{
  return yyyy;
} // END function getYear for Date class


int Date::getMonth() const
{
  return mm;
} // END function getMonth for Date class


int Date::getDay() const
{
  return dd;
} // END function getDay for Date class

/****************************************************************************
 *                Date class overloaded boolean operators                   *
 ****************************************************************************/

bool Date::operator ==(const Date& rhs)  const
{
  return ( this->yyyy == rhs.yyyy && this->mm == rhs.mm && this->dd == rhs.dd);
} // END overloaded operator ==


bool Date::operator !=(const Date& rhs) const
{
  return !( *this == rhs);
} // END overloaded operator !=


bool Date::operator <=(const Date& rhs) const
{
  return !( *this > rhs );
} // END overloaded operator <=


bool Date::operator <(const Date& rhs) const
{
  return !( *this >= rhs );
} // END overloaded operator <


bool Date::operator >=(const Date& rhs) const
{
  return ( *this > rhs || *this == rhs );
} // END overloaded operator >=


bool Date::operator >(const Date& rhs) const
{
  bool ans = false;

  if ( this->yyyy > rhs.yyyy ) // if lhs year is greater, then the left date is greater
    ans = true;
  
  else if ( (this->yyyy == rhs.yyyy) && (this->mm > rhs.mm) )
    ans = true;
  
  else if ( (this->yyyy == rhs.yyyy) && (this->mm == rhs.mm) && (this->dd > rhs.dd) )
    ans = true;

  return ans;
  
} // END overloaded operator >



/****************************************************************************
 *                                                                          *
 *               function readDoubleQuotedString implementation             *
 *                                                                          *
 ****************************************************************************/


std::string readDoubleQuotedString( std::istream& in )
{
  char quote;
  string message;

  in >> quote;
  getline(in, message, '\"');

  return message;
} // END function readDoubleQuotedString for Date class