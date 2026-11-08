//Samuel Smethers
//Linked list to use in hash table to chain in separate bins
#ifndef SeparateChaining_h
#define SeparateChaining_h

#include "Facilities.h"

class Chain{

    public:
    
    //constructor
    Chain();

    //destructor
    ~Chain();

    //add facility to end list
    void addFacility(const Facilities& tempFac);

    //check if chain is empty
    bool isEmpty() const;

    //search for ID in chain
    Facilities* searchID(string inputID);

    private:

        struct Node{
            Facilities data;
            Node* next;
            Node(const Facilities& tempFac)
            {
                data = tempFac;
                next = nullptr;
            }
        };
        Node* front;
        Node* rear;
        int count;
};

#endif