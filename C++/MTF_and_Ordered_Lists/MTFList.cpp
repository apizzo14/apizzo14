
#include "Node.cpp"
#include <chrono>

using namespace std;

// Templatized CLASS MTFList
template <typename T>
class MTFList
{
public:
    Node<T> *header;
    Node<T> *trailer;

    MTFList();
    ~MTFList();

    void add(T);
    void search(T, int&, double&);

}; //END declaration templatized class LL



// MTFList default constructor
template<typename T>
MTFList<T>::MTFList() {
    header = NULL;
    trailer = NULL;
}


// MTFList class destructor deletes all nodes of the linked list
template <typename T>
MTFList<T>::~MTFList()
{ // clear the linked list
    Node<T> *temp = header;
    while(temp != NULL){
        Node<T> *deleteThis = temp;
        temp = temp->next;
        delete deleteThis;
    }

}


// MTFList function add()
template <typename T>
void MTFList<T>::add(T data) {
    Node<T> *temp = new Node<T>;
    temp->info = data;
    temp->next = header;

    if(header == NULL && trailer == NULL){
        header = temp;
        trailer = temp;
    }
    else{
        header = temp;
    }

} // END MTF function add()


// MTFList function search()
template <typename T>
void MTFList<T>::search(T data, int &totalTraverse, double &totalTime) {
    bool found = false;
    int traversalCount = 1;

    // record start time
    auto timeStart = chrono::steady_clock::now();

    // if header is searched-for value, do nothing
    if (header->info == data){
        // searched for value is already in front of list, nothing to do, cost = 1
    }
    else { // searched for value is not header
        Node<T> *temp = header;
        while (!found && temp != trailer) {
            traversalCount += 1;
            if (temp->next->info == data) {
                found = true;
                // move found node to front of list
                Node<T> *found = temp->next;
                temp->next = temp->next->next;
                found->next = header;
                header = found;
            }
            else {
                temp = temp->next;
            }
        } // END while temp is not trailer
    } // END else condition, searched for isn't header

    auto timeEnd = std::chrono::steady_clock::now();

    // calculate elapsed time, convert to nanoseconds
    double elapsed_time_ns = chrono::duration_cast<chrono::nanoseconds>(timeEnd - timeStart).count();

//    cout << "MTFList Traversal Count: " << traversalCount << endl;
//    cout << "MTFList time: " << elapsed_time_ns << " nanoseconds" << endl << endl;

    // add values to total counts
    totalTraverse += traversalCount;
    totalTime += elapsed_time_ns;


} // END MTFList function add

