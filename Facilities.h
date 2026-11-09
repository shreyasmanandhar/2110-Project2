//Samuel Smethers
//object for facilities

#ifndef Facilities_h
#define Facilities_h

#include <iostream>
#include <string>

class Facilities{

    public:

        //constructor
        Facilities();

        //getters
        std::string getID() const;
        std::string getFacName() const;
        std::string getBuildName() const;
        std::string getCat() const;

        //setters
        void setID(std::string input);
        void setFacName(std::string input);
        void setBuildName(std::string input);
        void setCat(std::string input);

        //copy constructor
        Facilities& operator=(const Facilities& rhs);

        //display
        void displayFac() const;

    private:

        std::string facilityID;
        std::string facilityName;
        std::string buildingName;
        std::string category;
};

#endif