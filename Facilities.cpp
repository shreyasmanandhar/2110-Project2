#include "Facilities.h"

//constructor
Facilities::Facilities()
{
    facilityID = "Empty";
    facilityName = "Empty";
    buildingName = "Empty";
    category = "Empty";
}

//getters
string Facilities::getID() const{
    return facilityID;
}
string Facilities::getFacName() const{
    return facilityName;
}
string Facilities::getBuildName() const{
    return buildingName;
}
string Facilities::getCat() const{
    return category;
}

//setters
void Facilities::setID(string input){
    facilityID = input;
}
void Facilities::setFacName(string input){
    facilityName = input;
}
void Facilities::setBuildName(string input){
    buildingName = input;
}
void Facilities::setCat(string input){
    category = input;
}

//copy
Facilities& Facilities::operator=(const Facilities& rhs){
    if(this != &rhs)
    {
        facilityID = rhs.getID();
        facilityName = rhs.getFacName();
        buildingName = rhs.getBuildName();
        category = rhs.getCat();
    }
    return *this;
}