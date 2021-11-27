/*
*  main.cpp                                 
*                                                
*  COSC 051 Fall 2020                          
*  Project #4                                    
*                                                
*  Due on: 16 November 2020                  
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

/*
This menu-droven program will allow the user to calculate the total number of goods, along with
their cost, by reading distribution and price data files and object oriented programs with classes
Order and Prices.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;


// global constants

const int MilkCaseSize = 8,
          CheeseCaseSize = 4,
          MeatCaseSize = 8;


/****************************************************************************
 *                                                                          *
 *                        class Order declaration                           *
 *                                                                          *
 ****************************************************************************/

class Order 
{
  friend istream& operator>>(istream& is, Order& rhs);
  friend ostream& operator<<(ostream& os, const Order& rhs);
  
  public:
    Order();
    Order(unsigned int new_milk, 
          unsigned int new_cheese, 
          unsigned int new_meat);
    
    void setMilk(unsigned int new_milk) { milk = new_milk; };
    void setCheese(unsigned int new_cheese) {cheese = new_cheese; };
    void setMeat(unsigned int new_meat) { meat = new_meat; };

    unsigned int getMilk() const { return milk; };
    unsigned int getCheese() const { return cheese; };
    unsigned int getMeat() const { return meat; };

  private:
    unsigned int milk;
    unsigned int cheese;
    unsigned int meat;

}; // END declaration class Order


/****************************************************************************
 *                                                                          *
 *                        class Prices declaration                          *
 *                                                                          *
 ****************************************************************************/

class Prices 
{
  friend istream& operator>>(istream& is, Prices& rhs);
  friend ostream& operator<<(ostream& os, const Prices& rhs);

  public: 
    Prices();
    Prices(double new_milk, double new_cheese, double new_meat);
    
    void setMilk(double new_milk) { milkPrice = new_milk; };
    void setCheese(double new_cheese) { cheesePrice = new_cheese; };
    void setMeat(double new_meat) { meatPrice = new_meat; };

    double getMilk() const { return milkPrice; };
    double getCheese() const { return cheesePrice; };
    double getMeat() const { return meatPrice; };
  
  private:
    double milkPrice;
    double cheesePrice;
    double meatPrice;

}; // END declaration class Prices


/****************************************************************************
 *                                                                          *
 *               prototypes for stand-alone functions                       *
 *                                                                          *
 ****************************************************************************/

char displayMenu();

void loadDistributionFile(vector<Order>& orders,
                          string filename); 

void showItems(const vector<Order>& orders); 

void loadPriceFile(Prices& prices,
                   string filename); 

void showPrices(const Prices& prices);

void countCases(const vector<Order>& orders,
               unsigned int & milk_cases,
               unsigned int & cheese_cases,
               unsigned int & meat_cases); 

unsigned int countMilk(const vector<Order>& vec);

unsigned int countCheese(const vector<Order>& vec);

unsigned int countMeat(const vector<Order>& vec);

unsigned int casesNeeded(unsigned int items, unsigned int caseSize);

void showCosts(const vector<Order>& orders,
               const Prices& prices); 


// main function
int main()
{
    vector<Order> orders;
    Prices prices;
    unsigned int milkCases,
                 cheeseCases,
                 meatCases;
    string filename;
    char choice;
    bool loop = true;


    // greeting
    cout << "Hello! Welcome to the Food Bank System.\n\n";

    // display menu and get user choice
    choice = displayMenu();
    
    // loop so that menu is displayed until user enters 'Q'
    while( loop )
    {
        
        if ( choice == 'L' || choice == 'l' )
        { // load distribution file
            cout << "Please enter the distribution file path and name.\n"; // prompt user for file
            cin >> filename;
            loadDistributionFile( orders, filename );
            choice = displayMenu();
        } // end L menu option

        else if ( choice == 'K' || choice == 'k' )
        { // output table with distribution data
            showItems( orders );
            choice = displayMenu();
        } // end K menu option

        else if ( choice == 'P' || choice == 'p' )
        { // load price file
            cout << "Please enter the price file path and name.\n"; // prompt user for file
            cin >> filename;
            loadPriceFile( prices, filename );
            choice = displayMenu();
        } // end P menu option

        else if ( choice == 'O' || choice == 'o' ) 
        { // output data from price file
            showPrices( prices );
            choice = displayMenu();
        } // end O menu option

        else if ( choice == 'C' || choice == 'c' )
        {
            // display case count, price per case, and price
            showCosts( orders, prices );

            choice = displayMenu();
        } // end C menu option

        else if ( choice == 'W' || choice == 'w' )
        { // clear distribution data stored in vectors and data stored from price file
            orders.clear();
            prices.setMilk(0);
            prices.setCheese(0);
            prices.setMeat(0);
        
            cout << "Loaded data cleared. Returning to the menu.\n\n";
            choice = displayMenu();
        } // end W menu option

        else if ( choice == 'Q' || choice == 'q' )
        { // if user enters Q, loop is false and exits
            loop = false;
        } 

        else
        { // if user entered invalid char
            cout << "Invalid Input. Please enter either 'L, K, P, O, C, W, or Q.'\n";
            cout << "Returning to the menu.\n\n";
            choice = displayMenu();
        } // end invalid input error
    
    } // end menu loop
    
    // exit message
    cout << "Exiting the Food Bank System. Have a great day!\n";
    return 0;

} // end main function





/****************************************************************************
 *                                                                          *
 *   Overloaded stream insertion and extraction operators for Order class   *
 *                                                                          *
 ****************************************************************************/

ostream& operator<<(ostream &os, const Order &rhsObj)
{   
    os << setw(10) << rhsObj.milk;
    os << setw(10) << rhsObj.cheese;
    os << setw(10) << rhsObj.meat;
    
    return os;
    
} //END overloaded stream insertion operator implementation for Order class


istream& operator>>(istream &os, Order &rhsObj)
{   
    os >> rhsObj.milk;
    os >> rhsObj.cheese;
    os >> rhsObj.meat;
    
    return os;
    
} //END overloaded stream extraction operator implementation for Order class

/****************************************************************************
 *                                                                          *
 *            class Order member function implementation code               *
 *                                                                          *
 ****************************************************************************/

Order::Order()
{
    milk = 0;
    cheese = 0;
    meat = 0;

} // END default constructor for Order class


Order::Order( unsigned int new_milk, unsigned int new_cheese, unsigned int new_meat )
{
    milk = new_milk;
    cheese = new_cheese;
    meat = new_meat;

} // END constructor with parameters for Order class





/****************************************************************************
 *                                                                          *
 *  Overloaded stream insertion and extraction operators for Prices class   *
 *                                                                          *
 ****************************************************************************/

ostream& operator<<(ostream &os, const Prices &rhsObj)
{   
    os << setprecision(2) << fixed << showpoint;

    os << setw(5) << "$" << rhsObj.milkPrice;
    os << setw(5) << "$" << rhsObj.cheesePrice;
    os << setw(5) << "$" << rhsObj.meatPrice;
    
    return os;
    
} //END overloaded stream insertion operator implementation for Prices class


istream& operator>>(istream &os, Prices &rhsObj)
{   
    os >> rhsObj.milkPrice;
    os >> rhsObj.cheesePrice;
    os >> rhsObj.meatPrice;
    
    return os;
    
} //END overloaded stream extraction operator implementation Prices class


/****************************************************************************
 *                                                                          *
 *           class Prices member function implementation code               *
 *                                                                          *
 ****************************************************************************/

Prices::Prices()
{
    milkPrice = 0.0;
    cheesePrice = 0.0;
    meatPrice = 0.0;

} // END default constructor for Prices class


Prices::Prices( double new_milk, double new_cheese, double new_meat )
{
    milkPrice = new_milk;
    cheesePrice = new_cheese;
    meatPrice = new_meat;

} // END constructor with parameters for Prices class





/****************************************************************************
 *                         function displayMenu                             *
 ****************************************************************************/
char displayMenu()
{ // display menu and recieve user input
    char i='A';

    cout << "Please enter the letter next to your desired option:\n";
    cout << "Load a distribution data file (L)\n";
    cout << "Display loaded distribution data (K)\n";
    cout << "Update case prices (P)\n";
    cout << "Print current case prices (O)\n";
    cout << "Calculate restocking quantities and prices (C)\n";
    cout << "Clear all loaded data (W)\n";
    cout << "Quit the program (Q)\n\n";

    cin >> i;
    cin.ignore(500, '\n'); // ingore extraneous input
    return i; // char i is returned to main function as user's choice
} // end function displayMenu


/****************************************************************************
 *                         function loadDistributionFile                    *
 ****************************************************************************/
void loadDistributionFile(vector<Order>& orders,
                          string filename)
{
    ifstream inFile;
    Order newOrder;

    // variables to read file then push back into vector
    unsigned int numMilk;
    unsigned int numCheese;
    unsigned int numMeat;

    inFile.open ( filename.c_str() ); // open file

    if ( !inFile ) // if file fails to open, user is returned to menu
        cout << "Error opening file. Returning to the menu.\n\n";

    else
    {
        // read lines of file, add integers to parallel vectors
        while ( inFile >> newOrder ) 
        {
            orders.push_back(newOrder);
        } // end read file loop

        inFile.close(); // close file

        cout << "Distribution file succesfully loaded. Returning to menu.\n\n";

    } // end successful file open condition
    
} // end function loadDistributionFile


/****************************************************************************
 *                         function showItems                               *
 ****************************************************************************/
void showItems(const vector<Order>& orders) 
{ // output table containing data from distribution file
    if ( orders.empty() )
    { // if no data to show, return user to menu
        cout << "There is no distribution data to show. Please load a file and try again.\n"; 
        cout << "Returning to the menu.\n\n";
    }
    else
    {
        // print table with loaded distribution data
        cout << "\n\nHere is the loaded distribution data:\n\n";

        // column headers
        cout << setw(17) << "Milk" << setw(10) << "Cheese" << setw(10) << "Meat\n"; 
        for (unsigned i = 0; i < orders.size(); i++)
        { // output data from distribution file
            cout << left << setw(7) << "Order " << i+1 << right << setw(9) 
            << orders[i] << endl;
        }
        cout << "\n\n Returning to menu.\n\n";
    }
    
} // end function showItems


/****************************************************************************
 *                         function loadPriceFile                           *
 ****************************************************************************/
void loadPriceFile(Prices& prices,
                   string filename) 
{
    ifstream inFile;

    inFile.open ( filename.c_str() ); // open file

    if ( !inFile ) // if file fails to open, user is returned to menu
        cout << "Error opening file. Returning to the menu.\n\n";

    else
    { // read through line of file, store prices
        inFile >> prices;

        cout << "Price file successfully loaded. Returning to menu.\n\n";
        inFile.close(); // close file
    }

} // end function loadPriceFile


/****************************************************************************
 *                         function showPrices                              *
 ****************************************************************************/
void showPrices(const Prices& prices)
{ // output data from price file
    // if no data file loaded, user is returned to menu
    if ( prices.getMilk() == 0.0 || prices.getCheese() == 0.0 || prices.getMeat() == 0.0 )
    {    
        cout << "No price file loaded. Please load one and try again.\n";
        cout << "Returning to the menu.\n\n";
    }
    else
    { // data file is loaded, output prices
        cout << "Here are the loaded prices:\n\n";
        cout << setw(10) << "Milk" << setw(10) << "Cheese" << setw(10) << "Meat\n";
        cout << "  " << prices << endl << endl;

        cout << "Returning to the menu.\n\n";
    }
    
} // end function showPrices


/****************************************************************************
 *                         function countCases                              *
 ****************************************************************************/
void countCases(const vector<Order>& orders,
               unsigned int & milk_cases,
               unsigned int & cheese_cases,
               unsigned int & meat_cases) 
{ // calculate case count and output total price
    int milkItems,
        cheeseItems,
        meatItems;

    // calculate number of food items using counting functions
    milkItems = countMilk( orders );
    cheeseItems = countCheese( orders );
    meatItems = countMeat( orders );

    // calculate number of cases using casesNeeded function
    milk_cases = casesNeeded( milkItems, MilkCaseSize );
    cheese_cases = casesNeeded( cheeseItems, CheeseCaseSize );
    meat_cases = casesNeeded( meatItems , MeatCaseSize );

} // end function countCases


/****************************************************************************
 *                         function countMilk                              *
 ****************************************************************************/
unsigned int countMilk(const vector<Order>& vec)
{
    int milkCount = 0;

    for (unsigned i = 0; i < vec.size(); i++)
    {
        milkCount += vec[i].getMilk();
    }
    
    return milkCount;
    
} // end function countMilk


/****************************************************************************
 *                         function countCheese                             *
 ****************************************************************************/
unsigned int countCheese(const vector<Order>& vec)
{
    int cheeseCount = 0;

    for (unsigned i = 0; i < vec.size(); i++)
    {
        cheeseCount += vec[i].getCheese();
    }

    return cheeseCount;
    
} // end function countCheese


/****************************************************************************
 *                         function countMeat                              *
 ****************************************************************************/
unsigned int countMeat(const vector<Order>& vec)
{
    int meatCount = 0;

    for (unsigned i = 0; i < vec.size(); i++)
    {
        meatCount += vec[i].getMeat();
    }

    return meatCount;
    
} // end function countMeat


/****************************************************************************
 *                         function casesNeeded                             *
 ****************************************************************************/
unsigned int casesNeeded(unsigned int items, unsigned int caseSize)
{ // calculate number of cases
    int numCases;

    if ( items % caseSize == 0)
    { // if there is no remainder individual items, case size is quotient
        numCases = items / caseSize;
        return numCases;
    } 

    else
    { // if there are extra individual items, round up case size
        numCases = items / caseSize + 1;
        return numCases;
    }
    
    
} // end function casesNeeded


/****************************************************************************
 *                         function showCosts                              *
 ****************************************************************************/
void showCosts(const vector<Order>& orders,
               const Prices& prices)
{
    unsigned int milk_cases,
                 cheese_cases,
                 meat_cases;
    
    if ( orders.empty() )
    { // if no file loaded, user is returned to menu
        cout << "No distrubtion file loaded. Please load one and try again.\n";
        cout << "Returning to the menu.\n\n";
    }
    
    else if ( prices.getMilk() == 0.0 || prices.getCheese() == 0.0 || prices.getMeat() == 0.0 )
    { // if no price file loaded, user is returned to menu
        cout << "No price file loaded. Please load one and try again.\n";
        cout << "Returning to the menu.\n\n";
    }

    else
    {
        // get case count for each item
        countCases( orders, milk_cases, cheese_cases, meat_cases );

        // output table containing case count, price per case, and total price for each food item
        cout<< "Here is your loaded data:\n\n";

        cout << setw(20) << "Cases" << setw(20) << "Case Price" << setw(20) << "Total\n";
        cout << "Milk" << setw(15) << milk_cases << setw(15) << "$" << prices.getMilk() << setw(15) 
        << "$" << milk_cases * prices.getMilk() << endl;
        cout  << "Cheese" << setw(13) << cheese_cases << setw(15) << "$" << prices.getCheese() 
        << setw(15) << "$" << cheese_cases * prices.getCheese() << endl;
        cout << "Meat" << setw(15) << meat_cases << setw(15) << "$" << prices.getMeat() << setw(15)
        << "$" << meat_cases * prices.getMeat() << endl << endl;

        cout << "Returning to the menu.\n\n";

    }

} // end function showCosts
