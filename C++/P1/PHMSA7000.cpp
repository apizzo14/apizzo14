/*
  *  PHMSA7000.cpp
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

 #include "PHMSA7000.h"


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **               class HazMat7k implementation code                       **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


std::ostream& operator<<(ostream &os, const HazMat7k &rhsObj)
{
  std::string errOutStream = "ERROR: in HazMat7k class overloaded operator<<\n";
    errOutStream += "the output stream is in a failed state, no processing can take place...\n";
    if (!os)
    {
        throw std::invalid_argument(errOutStream); // throw an invalid argument exception
    }
    // output all information on one line
      os << rhsObj.reportReceivedDate << " " << rhsObj.reportNumber << " " 
      << rhsObj.supplementalNumber << " \"" << rhsObj.reportType << "\" " << rhsObj.operatorID 
      << " \"" << rhsObj.name << "\" " << "\"" << rhsObj.operatorStreetAddress << "\" " << "\""
      << rhsObj.operatorCityName<< "\" " << rhsObj.operatorStateAbbreviation << " \"" 
      << rhsObj.operatorPostalCode << "\" " << rhsObj.localDate << " " << rhsObj.localTime << " \"" 
      << rhsObj.commodityReleasedType << "\" " << showpoint << setprecision(3) 
      << rhsObj.unintentionalReleaseBbls 
      << " " << rhsObj.intentionalReleaseBbls << " " << rhsObj.recoveredBbls << " " << rhsObj.fatal
      << " " << rhsObj.injure << " " << rhsObj.igniteInd << " " << rhsObj.explodeInd << " " 
      << rhsObj.preparedDate << " \"" << rhsObj.authorizerName << "\" \"" << rhsObj.authorizerEmail
      << "\" \"" << rhsObj.narrative << "\""; 
  

    return os; 
} // END overloaded stream insertion operator for HazMat7k class

     
std::istream& operator>>(istream &is, HazMat7k &rhsObj)
{
  // initialize local variables to extract values
  Date report_received_date, local_date, prepared_date;

  string report_number, supplemental_number, operator_id, operator_state_abbreviation, ignite_ind,
  explode_ind, 

  report_type, name_, operator_postal_code, operator_street_address, commodity_released_type, 
  operator_city_name, authorizer_name, authorizer_email, narrative_;

  Time local_time;

  double unintentional_release_bbls, intentional_release_bbls, recovered_bbls; 

  int fatal_, injure_;


  std::string errInStream = "ERROR: in HazMat7k class overloaded operator>>\n";
  errInStream += "the input stream is in a failed state, no processing can take place...\n";
  if (!is)
  {
    throw std::invalid_argument(errInStream);
  }

  //try
  //{ //supplemental number string or int? operator_id
    is >> report_received_date;
    is >> report_number;
    is >> supplemental_number;
    report_type = readDoubleQuotedString(is);
    is >> operator_id;
    name_ = readDoubleQuotedString(is);
    operator_street_address = readDoubleQuotedString(is);
    operator_city_name = readDoubleQuotedString(is);
    is >> operator_state_abbreviation;
    operator_postal_code = readDoubleQuotedString(is);
    is >> local_date;
    is >> local_time;
    commodity_released_type = readDoubleQuotedString(is);
    is >> unintentional_release_bbls >> intentional_release_bbls >> recovered_bbls >> fatal_ 
    >> injure_;
    is >> ignite_ind >> explode_ind;
    is >> prepared_date;
    authorizer_name = readDoubleQuotedString(is);
    authorizer_email = readDoubleQuotedString(is);
    narrative_ = readDoubleQuotedString(is);

    //set values for each private member of HazMat7k class
    rhsObj.setReportReceivedDate(report_received_date);
    rhsObj.setReportNumber(report_number);
    rhsObj.setSupplementalNumber(supplemental_number);
    rhsObj.setReportType(report_type);
    rhsObj.setOperatorID(operator_id);
    rhsObj.setName(name_);
    rhsObj.setOperatorStreetAddress(operator_street_address);
    rhsObj.setOperatorCityName(operator_city_name);
    rhsObj.setOperatorStateAbbreviation(operator_state_abbreviation);
    rhsObj.setOperatorPostalCode(operator_postal_code);
    rhsObj.setLocalDate(local_date);
    rhsObj.setLocalTime(local_time);
    rhsObj.setCommodityReleasedType(commodity_released_type);
    rhsObj.setUnintentionalReleaseBbls(unintentional_release_bbls);
    rhsObj.setIntentionalReleaseBbls(intentional_release_bbls);
    rhsObj.setRecoveredBbls(recovered_bbls);
    rhsObj.setFatal(fatal_);
    rhsObj.setInjure(injure_);
    rhsObj.setIgniteInd(ignite_ind);
    rhsObj.setExplodeInd(explode_ind);
    rhsObj.setPreparedDate(prepared_date);
    rhsObj.setAuthorizerName(authorizer_name);
    rhsObj.setAuthorizerEmail(authorizer_email);
    rhsObj.setNarrative(narrative_);
  //}
  //catch (invalid_argument &e)
  // {
  //   string garb;
  //   cout << "Caught invalid_argument exception in HazMat7k operator >>.\n";
  //   cout << e.what() << endl;
  //   cout << "Skipping this line...";
  //   getline(is, garb);
  // }

  return is;

} // END overloaded stream extraction operator implementation for HazMat7k class
 

//HazMat7k destructor
HazMat7k::~HazMat7k()
{
  // nothing to do here
}

 
// default constructor
HazMat7k::HazMat7k()
{ //set values to minimum value found in appendix   
  reportReceivedDate = Date();
  reportNumber = "14920001";         
  supplementalNumber = "";         
  reportType = "PHMSA F 7000-1";                 
  operatorID = "";                 
  name = "";                       
  operatorStreetAddress = "";      
  operatorCityName = "";           
  operatorStateAbbreviation = "";  
  operatorPostalCode = "";         
  localDate = Date();               
  localTime = Time();                    
  commodityReleasedType= "";      
  unintentionalReleaseBbls = 0.0 ;
  intentionalReleaseBbls = 0.0;
  recoveredBbls = 0.0;
  fatal = 0;                
  injure = 0;               
  igniteInd = "";         
  explodeInd = "";        
  preparedDate = Date();        
  authorizerName = "";    
  authorizerEmail = "";   
  narrative = "";  
}
 
void HazMat7k::summaryReport(ostream &os) const
{
  std::string errOutStream = "ERROR: in HazMat7k class function summaryReport\n";
  errOutStream += "the output stream is in a failed state, no processing can take place...\n";
  if (!os)
  {
      throw std::invalid_argument(errOutStream); // throw an invalid argument exception
  }

  //output relevant information
  os << std::setw(25) << "Report Number and Date: " << this->reportNumber << "  " << 
  this->reportReceivedDate<< endl;
  os << setw(25) << "Local Date and Time: " << this->localDate << "  " << this->localTime << endl;
  os << setw(25) << "Number of Injuries: " << this->injure << endl;
  os << setw(25) << "Number of Fatalities: " << this->fatal << endl;
  os << setw(25) << "Narrative Length: " << this->narrative.length() << endl;
  os << "Narrative:  " << this->narrative << endl << endl;
} // END function summaryReport for HazMat7k class
 

void HazMat7k::setReportNumber(string value)
{
  if (value.length() != 8) // validate for eight character report number
  {
    throw invalid_argument("The Report Number must be eight digits");
  }
  else if ( value.substr(0,4) != to_string(this->reportReceivedDate.getYear()))
  { // validate to make sure first four integers are the year of the report received date
    std::string inval_message = "The first four digits of the Report Number must be the year";
    inval_message += " the report was recieved";
    throw invalid_argument(inval_message);
  }
  else
  {
    reportNumber = value;
  }
} // END function setReportNumber for HazMat7k class
 

void HazMat7k::setReportType(string value)
{
  if ( value != "ORIGINAL" && value != "ORIGINAL FINAL" && 
  value != "SUPPLEMENTAL" && value != "SUPPLEMENTAL FINAL")
  {
    throw invalid_argument("The Report Type is invalid");
  }
  else
  {
    reportType = value;  
  }
} // END function setReportType for HazMat7k class
 
