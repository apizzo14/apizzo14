/*
  *  IncidentLog.cpp
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


#include "IncidentLog.h"

//IncidentLog constructor
IncidentLog::IncidentLog() 
{
  //nothing to do here
}

//IncidentLog destructor
IncidentLog::~IncidentLog()
{
  //nothing to do here
}


void IncidentLog::displayReports(string outputFileName) const
{
  std::ofstream outFile;

  outFile.open(outputFileName.c_str()); //open file outputFileName

  if (!outFile) // if file doesn't open, throw exception
  {
      cout << "File failed to open, check path and name: \n";
      cout << outputFileName << endl;
      throw logic_error("File failed to open");
  }

  this->displayReports( outFile ); //send ostream to displayReports to output reports

} // END function displayReports( string ) for class IncidentLog


void IncidentLog::displayReports(ostream &os) const
{
  std::string errOutStream = "ERROR: in displayReports function of the IncidentLog class<<\n";
  errOutStream += "the output stream is in a failed state, no processing can take place...\n";
  if (!os)
  {
    throw std::invalid_argument(errOutStream); // throw an invalid argument exception
  }

  for (unsigned int i=0; i<this->size(); i++)
  { // output the summaries of the reports
    this->allIncidents.at(i).summaryReport( os );
  }
} // END function displayReports( ostream ) for class IncidentLog


HazMat7k& IncidentLog::find(string incidentNum)
{
  for (unsigned int i=0; i < this->size(); i++) //traverse the vector to find incidentNum
  { 
    if (this->allIncidents.at(i).getReportNumber() == incidentNum )
    { // if incidentNum is found, return the HazMat7k object reference
      return this->allIncidents.at(i);
    }
  }
  // object hasn't been returned, throw logic error
  throw logic_error("No report with this Incident Number has been loaded.\n");
} // END function find for class IncidentLog


void IncidentLog::read( string inputFileName )
{
  ifstream inFile;
  inFile.open( inputFileName.c_str()); // open file
  
  if (!inFile) // if file doesn't open, throw exception
  {
      cout << "File failed to open, check path and name: \n";
      cout << inputFileName << endl;
      throw std::runtime_error("File failed to open");
  }

  this->read( inFile ); // pass to second read function

  inFile.close(); // close the file
} // END function read( string ) for class IncidentLog

void IncidentLog::read( istream& in )
{
  HazMat7k report;
  string garbage;

  std::string errInStream = "ERROR: in IncidentLog class read function\n";
  errInStream += "the input stream is in a failed state, no processing can take place...\n";
  if (!in)
  {
    throw std::invalid_argument(errInStream);
  }
  while(in){
    try
    {
      in >> report; 
      this->allIncidents.push_back(report);
      cout << "Moving to the next report...\n";
    } // END try 

    catch (std::invalid_argument &e)
    { // catch invalid arguments
        cout << "Caught an exception in read function of IncidentLog\n";
        std::cout << e.what() << endl; // output error message
        cout << "Skipping this line. ";
        getline(in, garbage); // get rid of the rest of line w invalid date
    }
  }

} // END function read( istream ) for class IncidentLog

void IncidentLog::write( string outputFileName ) const
{
  std::ofstream outFile;

  outFile.open(outputFileName.c_str()); //open file outputFileName

  if (!outFile) // if file doesn't open, throw exception
  {
      cout << "File failed to open, check path and name: \n";
      cout << outputFileName << endl;
      throw logic_error("File failed to open");
  }
  
  this->write( outFile );

  outFile.close(); // close the file
} // END function write( string ) for class IncidentLog


void IncidentLog::write( ostream& out ) const
{
  std::string errOutStream = "ERROR: in write function of the IncidentLog class<<\n";
  errOutStream += "the output stream is in a failed state, no processing can take place...\n";
  if (!out)
  {
      throw std::invalid_argument(errOutStream); // throw an invalid argument exception
  }

  for (unsigned int i=0; i<this->allIncidents.size(); i++)
  {
    out << this->allIncidents.at(i);
    out << endl;
  }

  cout << "OK. The output file has been written.\n";

} // END function write( ostream ) for class IncidentLog