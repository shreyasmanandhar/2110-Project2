//Samuel Smethers
//Linked list to use in hash table to chain in separate bins
#ifndef SeparateChaining_h
#define SeparateChaining_h

#include "Facilities.h"

struct Node{
    Facilities data;
    Node* next;
    Node(const Facilities& tempFac)
    {
        data = tempFac;
        next = nullptr;
    }
};

class Chain{

    public:

    //constructor
    Chain();

    ~Chain();

    Chain(const Chain&) = delete;
    Chain& operator=(const Chain&) = delete;

    //destructor
    void RemoveChain();

    //add facility to end list
    void addFacility(const Facilities& tempFac);

    //check if chain is empty
    bool isEmpty() const;

    //search for ID in chain
    Facilities* searchID(std::string inputID);

    //check for duplicate
    bool isDuplicate(std::string tempID);

    void printAll() const;

    private:

        Node* front;
        Node* rear;
        int count;
};

#endif
