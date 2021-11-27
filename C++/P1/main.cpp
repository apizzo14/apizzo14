/*
  *  main.cpp
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

 #include "main.h"


 int main(int argc, const char * argv[])
 { 
   IncidentLog incidents, incidents2;
   string outputFile;
   string fileName = "";
   string findThis;
   HazMat7k found;

   /*
   string errMsg1 = "Must pass input file name and complete path as command line argument\n";
   if (argc < 2) // if command line arguments are invalid, throw error
   {
      throw invalid_argument(errMsg1); 
   }
   */
   try
   {
      
      fileName = string(argv[1]); // take fileName from second command line arguent

      incidents.read(fileName.c_str()); // read the file
      

      // print total number of HazMat objects
      cout << "Total records number " << incidents.size() << endl;

      //display summaries of the reports loaded
      cout << "Here are the reports:" << endl;
      incidents.displayReports( );
/*
      // write an output file
      cout << "What would you like to title the output file?\n";
      cin >> outputFile;
      incidents.write( outputFile.c_str());
      
      // find an incident by the incident number input by user
      cout << "Enter the Incident Report Number of the report you'd like to find:\n";
      cin >> findThis;
      found = incidents.find(findThis); // use find function of IncidentsLog
      cout << "Here is the information on the report:\n";
      found.summaryReport(); // output report summary
  */    

     bool test1, test2, test3, test4, test5;
     Date date1;
     date1.setDate(2021, 9, 29);
     Date date2;
     date2.setDate(2001, 7, 31);
     Date date3;
     date3.setDate(2001,7,31);
     Date date4;
     date4.setDate(1999, 9, 19);

     test1 = date1 == date2;
     test2 = date2 == date3;
     test3 = date3 == date4;
     test4 = date4 == date1;

     //test3 = 12/6/1999 == 12/1/2001;
     
      if(test1)
         cout << "1>2, test 1 true\n";
      else
         cout << "1>2, test 1 false\n";
   
      if(test2)
         cout << "2=3, test 2 true\n";
      else
         cout << "2=3, test 2 false\n";
      
      if(test3)
         cout << "3>4, test 3 true\n";
      else
         cout << "3>4, test 3 false\n";

      if(test4)
         cout << "4<1, test 4 true\n";
      else
         cout << "4<1, test 4 false\n";

      HazMat7k HazMatObj;

      cout << HazMatObj;




      cout << endl << endl;
      Date date5(2021, 9, 29);
      cout << date5 << endl;

      Date date6(date4);
      cout << date6 << endl;

   }

   catch ( invalid_argument &e)
	{
		cout << "caught invalid_argument exception in function main.\n";
		cout << e.what() << endl;
	}

   catch ( logic_error &e)
   {
      cout << "caught logic_error exception in function main.\n";
      cout << e.what() << endl;
   }

   catch ( ... )
   {
      cout << "caught unknown exception in function main" << endl;
   }

   return 0;

 } // END main function

 