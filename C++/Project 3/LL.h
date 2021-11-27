/*
  *  LL.h
  *
  *  COSC 052 Fall 2021
  *  Project #3
  *
  *  Due on: OCT 28, 2021
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






#ifndef _COSC052_FALL2021_P3_LL_h_
#define _COSC052_FALL2021_P3_LL_h_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "Exceptions.h"
#include "Resources.h"

#define DEBUG_LL_POP_BACK
//#define DEBUG_COPY_LIST
//#define DEBUG_LL_INSERT

using std::vector;
using std::string;
using std::endl;
using std::cout;


const int LOOP_OUTPUT_FREQUENCY = 5000;   //new for P3 (optional)
const int SORT_OUTPUT_FREQUENCY = 750;    //new for P3 (optional)

/**********************************************************
 *                                                        *
 *                                                        *
 *                  Project #3 classes                    *
 *                                                        *
 *                                                        *
 **********************************************************/



/****************************************************************************
 *                                                                          *
 *                       class Node declaration                             *
 *                                                                          *
 ****************************************************************************/


template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node<T> *previous;

    Node(T = T(), Node<T> *next = NULL, Node<T> *previous = NULL);

}; //END declaration templatized class Node



/****************************************************************************
 *                                                                          *
 *                        class LL declaration                              *
 *                                                                          *
 ****************************************************************************/


template <typename T>
class LL
{
    template <typename F>
    friend std::ostream& operator<<(std::ostream& os, const LL<F> &rhsObj);

private:
    unsigned count;
    Node<T> *header;
    Node<T> *trailer;
    void copyList(const LL<T>&);
    void initialize();

    void remove(unsigned ndx);

public:
    LL();
    LL(const LL<T>&);
    ~LL();

    LL<T>& operator=(const LL<T>&);

    void insert(unsigned ndx, T);

    void push_back(T);
    void pop_back();
    T& back() const;

    void push_front(T);
    void pop_front();
    T& front() const;

    void clear();
    bool empty() const;
    unsigned size() const {return count;}

    T& at(unsigned ndx) const;
    T& operator[](unsigned ndx) const;

    T* toArray() const;

    void bubbleSort();
    void selectionSort();
    void insertionSort();
    unsigned linearSearch(T lookFor) const;
    unsigned binarySearch(T lookFor) const;


}; //END declaration templatized class LL




/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                      class Node implementation                         **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



/****************************************************************************
 *                         default constructor                              *
 ****************************************************************************/

template <typename T>
Node<T>::Node(T infoValue, Node<T> *nPtr, Node<T> *pPtr)
{ // send members to passed values
    info = infoValue;
    next = nPtr;
    previous = pPtr;

} //END Node<T>::Node(T infoValue, Node *nodePtr)


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                       class LL implementation                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



/****************************************************************************
 *              non-member function overloaded operator<<                   *
 ****************************************************************************/

template <typename T>
std::ostream& operator<<(std::ostream& os, const LL<T> &rhsObj)
{
    Node<T> *current = rhsObj.header->next; // set current to first non-sentinel Node in list

    while (current != rhsObj.trailer)
    { // traverse list and output values
        os << current->info << endl;
        current = current->next;
    }

    return os;

} //END overloaded stream insertion operator for LL<T> class



/****************************************************************************
 *                  private method copyList of LL class                     *
 ****************************************************************************/

template <typename T>
void LL<T>::copyList(const LL<T> &otherLL)
{
    //cout << "Entered copyList" << endl;

    if (!(this->empty()))
    { // if list is not empty, delete contents
        this->clear();
    }
    //cout << "List is clear." << endl;
    for (unsigned int i=0; i < otherLL.count; i++)
    { // push back each member of list to copy
        this->push_back(otherLL.at(i));
    }
} //END function copyList(const LL &otherLL)



/****************************************************************************
 *                 private method initialize of LL class                    *
 ****************************************************************************/

template <typename T>
void LL<T>::initialize()
{ // set up sentinel nodes, set count to zero
    header->next = trailer;
    header->previous = header;
    trailer->previous = header;
    trailer->next = trailer;

    count = 0;

} //END private method LL<T>::initialize



/****************************************************************************
 *                 private method remove of LL class                    *
 ****************************************************************************/

template <typename T>
void LL<T>::remove(unsigned ndx)
{
    if (ndx > count-1 || ndx < 0)
    { // if index is out of range, throw exception
        throw out_of_range("Error in LL function remove. Index must be in [0, count - 1]");
    }

    if (this->empty())
    { // if list is empty throw exception
        throw no_such_object("Error in LL function remove. The list is empty.");
    }

    Node<T> *after = header->next;
    for (unsigned int i=0; i < (ndx+1); i++)
    { // traverse list to get to node after one to be deleted
        after = after->next;
    }
    Node<T> *before = after->previous->previous;
    delete after->previous; // delete node, rearrange pointers
    before->next = after;
    after->previous = before;

    count--;

} // END remove member function of class LL



/****************************************************************************
 *                         default constructor                              *
 ****************************************************************************/

template <typename T>
LL<T>::LL()
{ // dynamically allocate header and trailer, call initialize()
    header = new Node<T>;
    trailer = new Node<T>;

    this->initialize();

} //END default constructor for LL class



/****************************************************************************
 *                    copy constructor of LL class                          *
 ****************************************************************************/

template <typename T>
LL<T>::LL(const LL<T> &otherLL)
{ // initialize new list, call copyList function
    header = new Node<T>;
    trailer = new Node<T>;
    this->initialize();
    this->copyList( otherLL );

} //END LL<T>::LL(const LL<T> &otherLL)



/****************************************************************************
 *                         destructor of LL class                           *
 ****************************************************************************/

template <typename T>
LL<T>::~LL()
{ // clear the linked list, delete sentinels
    this->clear();
    delete header;
    delete trailer;
    header = NULL;
    trailer = NULL;

} //END LL<T>::~LL()



/****************************************************************************
 *                 member function overloaded operator=                     *
 ****************************************************************************/


template <typename T>
LL<T>& LL<T>::operator=(const LL<T> &rhsLL)
{
    if (!(this->header == rhsLL.header && this->trailer == rhsLL.trailer
            && this->count == rhsLL.count)) // ensure lists are not equal
    { // clear list then call copyList
        cout << "Clearing..." << endl;
        this->clear();
        cout << "Copying..." << endl;
        this->copyList(rhsLL);
    }

    return *this;

} // END LL<T>::operator=(const LL<T> &rhsLL)



/****************************************************************************
 *                         member function insert                           *
 ****************************************************************************/

template <typename T>
void LL<T>::insert(unsigned ndx, T infoToAdd)
{
    if ( ndx > this->count || ndx < 0)
    { // if index is out of range, throw exception
        throw out_of_range("Error in function insert. Index is out of range.");
    }

    Node<T> *addMe = new Node<T>(infoToAdd, NULL, NULL); //dynamically allocate new node
    Node<T> *after = header->next;
    for (unsigned int i=0; i < (ndx); i++)
    { // traverse list to get to node after
        after = after->next;
    }
    Node<T> *before = after->previous; // adjust pointers to add the new node
    addMe->next = after;
    addMe->previous = before;
    after->previous = addMe;
    before->next = addMe;

    count++;

} //END member function insert



/****************************************************************************
 *                        member function push_back                         *
 ****************************************************************************/

template <typename T>
void LL<T>::push_back(T infoToAdd)
{

#ifdef DEBUG_LL_PUSH_BACK
    cout << "Entered function LL<T>::push_back() " << endl;
#endif
    // use function insert with index of count to add to end of the list
    this->insert( this->count, infoToAdd);

#ifdef DEBUG_LL_PUSH_BACK
    cout << "Exiting function LL::push_back() " << endl;
#endif

} //END LL<T>::push_back(T infoToAdd)



/****************************************************************************
 *                        member function pop_back                          *
 ****************************************************************************/

template <typename T>
void LL<T>::pop_back()
{ // use function remove with the index of count -1
    this->remove(this->count-1);

} //END LL<T>::pop_back()



/****************************************************************************
 *                          member function back                            *
 ****************************************************************************/

template <typename T>
T& LL<T>::back() const
{
    if (this->empty())
    { // if the list is empty, throw exception
        throw no_such_object("Error in function back. The list is empty.");
    }
    else
    { // return the last node in list
        return this->at(count-1);
    }

} // END function back, class LL



/****************************************************************************
 *                       member function push_front                         *
 ****************************************************************************/

template <typename T>
void LL<T>::push_front(T infoToAdd)
{ // use insert method with index of zero to add new node at beginning of list
    insert(0, infoToAdd);

} //END LL::push_front(T infoToAdd)



/****************************************************************************
 *                       member function pop_front                          *
 ****************************************************************************/

template <typename T>
void LL<T>::pop_front()
{ // remove node at index 0
    this->remove(0);

} //END LL<T>::pop_front()



/****************************************************************************
 *                          member function front                           *
 ****************************************************************************/

template <typename T>
T& LL<T>::front() const
{
    if (this->empty())
    { // if list is empty throw exception
        throw no_such_object("Error in function front. The list is empty.");
    }
    else
    { // return first node
        return this->at(0);
    }

} // END method front of class LL



/****************************************************************************
 *                         member function clear                            *
 ****************************************************************************/

template <typename T>
void LL<T>::clear()
{
    Node<T> *current = header;

    while ( header->next != trailer)
    { // pop back all nodes in the list
        this->pop_back();
    }

    this->initialize();

} //END LL<T>::clear()



/****************************************************************************
 *                        method empty of LL class                          *
 ****************************************************************************/

template <typename T>
bool LL<T>::empty() const
{
    bool answer = false;

    if (header->next == trailer)
    { // if header next is trailer, list is empty
        answer = true;
    }

    return answer;

} // END LL<T>::empty



/****************************************************************************
 *                         member function at const                         *
 ****************************************************************************/

template <typename T>
T& LL<T>::at(unsigned location) const
{
    if ( location > (this->count)-1 || location < 0)
    { // if index is out of range, throw exception
        throw out_of_range("Error in function at. Index is out of range.");
    }
    if (this->empty())
    { // if list is empty, throw exception
        throw out_of_range("Error in function at. The list is empty.");
    }

    Node<T> *current = header->next;
    for( unsigned int i=0; i < location; i++)
    { // traverse to get to node at index location
        current = current->next;
    }

    return current->info;

} //END LL::at(int location)



/****************************************************************************
 *                       overloaded operator[] const                        *
 ****************************************************************************/

template <typename T>
T& LL<T>::operator[](unsigned ndx) const
{ // return info stored in node at index ndx
    return this->at(ndx);

} //END overloaded subscript operator



/****************************************************************************
 *                         member function toArray                          *
 ****************************************************************************/

template <typename T>
T* LL<T>::toArray() const
{
    T* thisArray = new T[count]; // create dynamic array
    for (unsigned int i=0; i < count; i++)
    { // assign each index of array to node of that index
        thisArray[i] = this->at(i);
    }

    return thisArray;

} // END LL<T>::toArray()



/****************************************************************************
 *                       member function bubbleSort                         *
 ****************************************************************************/

template <typename T>
void LL<T>::bubbleSort()
{
    cout << "Entered member function bubbleSort()" << endl;

    unsigned swapCount = 0;

    T temp;
    int iteration = 0;
    int index = 0;

    bool hadSwap = true;

    for ( iteration = 1; iteration < this->count && hadSwap; iteration++ )
    { // iterate through array
        hadSwap = false;
        for ( index = 0; index < this->count - iteration; index++ )
        { // swap to the back of the list
            #ifdef __DEBUG_BUBBLE_SORT__
            cout << "checking order " << list[index] << " " << list[index+1] << endl;
            #endif
            if ( this->at(index) > this->at(index+1) )
            { // if out of order, swap two items
                #ifdef __DEBUG_BUBBLE_SORT__
                cout << "swapping values" << endl;
                #endif
                hadSwap = true;
                temp = this->at(index);
                this->at(index) = this->at(index+1);
                this->at(index+1) = temp;

                swapCount ++;
            }

        } // END inner loop

    } // END outer loop

    cout << "Exiting member function bubbleSort() \nresults: swapCount = " << swapCount << endl;

} //END member function LL<T>::bubbleSort()



/****************************************************************************
 *                     member function selectionSort                        *
 ****************************************************************************/

template <typename T>
void LL<T>::selectionSort()
{
    cout << "Entered function selectionSort() " << endl;

    unsigned swapCount = 0;

    int index;
    int smallestIndex;
    int location;
    int temp;

    for (index=0; index < this->count -1; index++)
    {
        smallestIndex = index;

        for (location = index+1; location < this->count; location++)
        { // find smallest number in list
            if (this->at(location)<this->at(smallestIndex))
                smallestIndex = location;
        }

        temp = this->at(smallestIndex);
        this->at(smallestIndex) = this->at(index); //set it to front of unsorted list
        this->at(index)= temp;

        swapCount++;
    }

    cout << "Exiting function selectionSort() \nresults: swapCount = " << swapCount << endl;

} // END void LL<T>::selectionSort()



/****************************************************************************
 *                     member function insertionSort                        *
 ****************************************************************************/

template <typename T>
void LL<T>::insertionSort()
{
    cout << "Entered function insertionSort() " << endl;

    unsigned swapCount = 0;

    int firstOutOfOrder, location;
    int temp;

    for (firstOutOfOrder = 1; firstOutOfOrder < this->count; firstOutOfOrder++)
    {
        if (this->at(firstOutOfOrder) < this->at(firstOutOfOrder -1))
        { // set out of order to front of list
            temp = this->at(firstOutOfOrder);
            location = firstOutOfOrder;

            do
            { // push all other numbers back
                this->at(location) = this->at(location -1);
                location--;
            }
            while (location >0 && this->at(location-1) > temp) ;

            this->at(location) = temp;

            swapCount++;

        }
    }

    cout << "Exiting function insertionSort() \nresults: swapCount = " << swapCount << endl;

} // END void LL<T>::insertionSort()



/****************************************************************************
 *                      member function linearSearch                        *
 ****************************************************************************/

template <typename T>
unsigned LL<T>::linearSearch(T lookFor) const
{
    if (this->empty())
        throw no_such_object("Error in linearSearch method. List is empty.");

    cout << "Entered function linearSearch(" << lookFor << ")" << endl;

    unsigned index = 0;

    int loc = 0;
    bool found = false;

    while (loc < this->count && !found)
    { // iterate through array to find lookFor
        if (this->at(loc) == lookFor)
        {
            found = true;
            index = loc;
        }
        else
        {
            loc++;
        }
    } // end while to search list

    if (!found)
        throw no_such_object("Error in function linearSearch. Value not found in this list.");


    cout << "Exiting function linearSearch()" << endl;

    //return index of the found item
    return index;


} // END unsigned LL<T>::linearSearch(T lookFor)



/****************************************************************************
 *                      member function binarySearch                        *
 ****************************************************************************/

template <typename T>
unsigned LL<T>::binarySearch(T lookFor) const
{
    cout << "Entered function binarySearch(" << lookFor << ")" << endl;

    if (this->empty())
        throw no_such_object("Error in linearSearch method. List is empty.");

    bool found = false;

    long  first = 0;
    long  last = size() - 1;
    long  middle  = 0;
    long position = 0;

    while (first <= last && !found)
    { //
        middle = (first + last)/2;
        if (this->at(middle) == lookFor)
            found = true;
        else if (this->at(middle) > lookFor) //change first and last to target area with unfound item
            last = middle - 1;
        else
            first = middle + 1;
    }

    if (found) // if found return index of found item
        return middle;
    else
        throw no_such_object("Error in function binarySearch. Value not found in this list");

    cout << "Exiting function binarySearch()" << endl;

} // END unsigned LL<T>::binarySearch(T lookFor)






#endif /*  _COSC052_FALL2021_P3_LL_h_  */

