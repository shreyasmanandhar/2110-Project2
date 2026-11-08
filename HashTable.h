#ifndef HashTable_h
#define HashTable_h

#include "SeparateChaining.h"
#include <vector>

const int M = 11; // const prime number for the table size to spread entries better

class HashTable
{
    public:

    //constructor
    HashTable();

    //destructor
    ~HashTable();

    //add a facility to the table
    void loadTable(Facilities& tempFac);

    //hash the key into the index
    void hash();

    //duplicate check
    bool isDuplicate(string facID);

    //find id
    void findID(string facID);

    private:

        int key;
        int index;
        int totalCount;
        Chain* table[M];

};

#endif