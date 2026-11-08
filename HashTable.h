#ifndef HashTable_h
#define HashTable_h

#include "SeparateChaining.h"
#include "CampusGraph.h"
#include <string>
#include <vector>

class HashTable
{
    public:

    static const int M = 11; // const prime number for the table size to spread entries better

    //constructor
    HashTable();

    //destructor
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void loadFacilities(const std::string& path, const CampusGraph& graph);

    //add a facility to the table
    bool loadTable(Facilities& tempFac);

    //hash the key into the index
    int hash(const std::string& id) const;

    //duplicate check
    bool isDuplicate(std::string facID);

    //find id
    void findID(std::string facID);

    void displayAll();

    private:

        int totalCount;
        int collisions;
        Chain* table[M];

};

#endif
