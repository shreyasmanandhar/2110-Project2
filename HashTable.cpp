#include "HashTable.h"

//constructor
HashTable::HashTable(){
    key = 0;
    index = 0;
    totalCount =0;
    for(int i =0; i <M; ++i) //iterate through and assign all initial pointers to null
    {
        table[i]==nullptr;
    }
}

//destructor
HashTable::~HashTable(){
    for(int i =0; i <M; ++i) //iterate through the pointers in the array and delete the chain at each location
    {
        table[i]->RemoveChain();
    }
}

//add a facility to the table
void HashTable::loadTable(Facilities& tempFac){
    string tempID = tempFac.getID();
    key = stoi(tempFac.getID());
    hash();
    
    if(table[index]->isEmpty())
    {
        table[index]->addFacility(tempFac);
        tempFac.displayFac();
        totalCount++;
    }
    else if(table[index]->isDuplicate(tempID))
    {
        cout<< "Not accepted, duplicate ID -> "<<tempFac.getID()<<'|'<<tempFac.getFacName()<<'|'<<tempFac.getBuildName()<<'|'<<tempFac.getCat()<<endl;
    }
    else
    {
        table[index]->addFacility(tempFac);
        tempFac.displayFac();
        totalCount++;
    }

}

//hash the key into the index
void HashTable::hash(){
    index = key % M;
}

//find id
void HashTable::findID(string facID){
    key = stoi(facID);
    hash();

    Facilities* found = table[index]->searchID(facID);

    if(found == nullptr)
    {
        cout<< "Vaild ID "<< facID <<" not found in table.";
    }
    else
    {
        cout<< "Found -> " <<found->getID()<<'|'<<found->getFacName()<<'|'<<found->getBuildName()<<'|'<<found->getCat()<<endl;
    }
}
