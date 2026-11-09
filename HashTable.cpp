#include "HashTable.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

using namespace std;

//constructor
HashTable::HashTable(){
    totalCount = 0;
    collisions = 0;
    for(int i =0; i <M; ++i) //iterate through and assign all initial pointers to null
    {
        table[i] = new Chain();
    }
}

//destructor
HashTable::~HashTable(){
    for(int i =0; i <M; ++i) //iterate through the pointers in the array and delete the chain at each location
    {
        delete table[i];
        table[i] = nullptr;
    }
}

void HashTable::loadFacilities(const std::string& path, const CampusGraph& graph){
    ifstream in(path.c_str());
    if (!in){
        printOpenError(path);
        printLoadSummary(path, 0, 0);
        return;
    }

    string line;
    int lineNum = 0, accepted = 0, rejected = 0;
    while (getline(in, line)){
        ++lineNum;
        if (isSkippable(line)) continue;

        vector<string> f = splitFields(line);
        if (f.size() != 4){
            printWarning(path, lineNum, "expected 4 fields, found " + to_string(f.size()));
            ++rejected;
            continue;
        }
        if (f[0].empty() || f[1].empty() || f[2].empty() || f[3].empty()){
            printWarning(path, lineNum, "empty field");
            ++rejected;
            continue;
        }

        int b = graph.findBuilding(f[2]);
        if (b == -1){
            printWarning(path, lineNum, "unknown building \"" + f[2] + "\"");
            ++rejected;
            continue;
        }

        Facilities fac;
        fac.setID(toUpper(f[0]));
        fac.setFacName(f[1]);
        fac.setBuildName(graph.getName(b));
        fac.setCat(f[3]);

        if (loadTable(fac)) ++accepted;
        else ++rejected;
    }
    printLoadSummary(path, accepted, rejected,
                     " (capacity " + to_string(M) + ", entries " + to_string(totalCount) +
                     ", collisions " + to_string(collisions) + ")");
}

//add a facility to the table
bool HashTable::loadTable(Facilities& tempFac){
    string tempID = tempFac.getID();
    int index = hash(tempID);

    if(table[index]->isDuplicate(tempID))
    {
        cout<< "Not accepted, duplicate ID -> "<<tempFac.getID()<<'|'<<tempFac.getFacName()<<'|'<<tempFac.getBuildName()<<'|'<<tempFac.getCat()<<endl;
        return false;
    }

    if(!table[index]->isEmpty())
    {
        collisions++;
    }
    table[index]->addFacility(tempFac);
    tempFac.displayFac();
    totalCount++;
    return true;
}

//hash the key into the index
int HashTable::hash(const string& id) const{
    unsigned long h = 0;
    for (size_t i = 0; i < id.size(); ++i)
    {
        h = h * 31 + static_cast<unsigned char>(id[i]);
    }
    return static_cast<int>(h % M);
}

bool HashTable::isDuplicate(string facID){
    string id = toUpper(trim(facID));
    return table[hash(id)]->isDuplicate(id);
}

//find id
void HashTable::findID(string facID){
    string id = toUpper(trim(facID));
    Facilities* found = table[hash(id)]->searchID(id);

    if(found == nullptr)
    {
        cout<< "Valid ID "<< facID <<" not found in table.\n";
    }
    else
    {
        cout<< "Found -> " <<found->getID()<<'|'<<found->getFacName()<<'|'<<found->getBuildName()<<'|'<<found->getCat()<<endl;
    }
}

void HashTable::displayAll(){
    if (totalCount == 0)
    {
        cout << "No facilities are loaded.\n";
        return;
    }
    for (int i = 0; i < M; ++i)
    {
        table[i]->printAll();
    }
}
