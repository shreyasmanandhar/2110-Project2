//Samuel Smethers
//object for facilities

#ifndef Facilities_h
#define Facilities_h

#include <string>
using namespace std;

class Facilities{

    public:

        //constructor
        Facilities();

        //getters
        string getID() const;
        string getFacName() const;
        string getBuildName() const;
        string getCat() const;

        //setters
        void setID(string input);
        void setFacName(string input);
        void setBuildName(string input);
        void setCat(string input);

        //copy constructor
        Facilities& operator=(const Facilities& rhs);

    private:

        string facilityID;
        string facilityName;
        string buildingName;
        string category;
};

#endif