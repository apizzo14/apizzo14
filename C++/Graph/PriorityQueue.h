//
// Priority Queue Class
//

#ifndef P4_PRIORITYQUEUE_H
#define P4_PRIORITYQUEUE_H

#include <chrono>
#include <string>
#include <iostream>
using namespace std;

class PriorityQueue{
public:
    Node *pq;
    int length;

    void enqueue(string ti, int pri);
    Node* dequeue();

    PriorityQueue();

    void printQueue();

};

void PriorityQueue::enqueue(string ti, int pri) {
    if(length == 0){
        // pq empty
        pq = new Node(ti, pri);
    }
    else if(length == 1){
        if(pri >= pq->cost){
            pq->next = new Node(ti,pri);
        }
        else{
            Node *temp = pq;
            pq = new Node(ti,pri, temp);
        }
    } // end length == 1
    else{
        // length 2+
        Node *follow = pq;
        if(pri < follow->cost){
            // insert at first pos
            pq = new Node(ti,pri, follow);
        }
        else {
            Node *lead = pq->next;
            while (pri >= lead->cost) {
                lead = lead->next;
                follow = follow->next;
                if (lead == nullptr)
                    break;
            }
            follow->next = new Node(ti, pri, lead);
        }
    } // end cond length == 2+
    length++;
}

Node* PriorityQueue::dequeue() {
    Node *temp = pq;
    pq = pq->next;
    length--;
    return temp;
    // in algorithm, dequeue and check if the title is end vertex, if it is get the total cost
}

PriorityQueue::PriorityQueue() {
    pq = nullptr;
    length = 0;
}

void PriorityQueue::printQueue() {
    Node *temp = pq;
    for(int i=0; i < length; i++){
        cout << temp->dest << " " << temp->cost << endl;
        temp = temp->next;
    }
    cout << endl;
}

#endif //P4_PRIORITYQUEUE_H
