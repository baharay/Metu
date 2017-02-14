#ifndef KINGDOM_H
#define KINGDOM_H

#include "House.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

using std::cout;
using std::endl;

class Kingdom {
	
	public:		
		Kingdom(string kingdomName, Religion kingdomReligion);
    	~Kingdom();

    	void assignGreatHouse(House* const greatHouse);
    	void dismissGreatHouse();

    	void addNobleHouse(House* const nobleHouse);
    	void removeNobleHouse(House* const nobleHouse);

        string getName();
        Religion getReligion();

        void setReligion(Religion religion);
        
    	House* getGreatHouse();
    	vector <House *> getNobleHouses();

        // Optional methods.
        void increaseDuelPoints();
        void increaseTotalDuelCount();

        int getTotalDuelCount();
        int getDuelPoints();
        // Optional methods
        
    private:
    	string name;
        Religion religion;

        int duelPoints;
        int totalDuelCount;

    	House *greatHouse;
    	vector<House *> nobleHouses;
};

#endif // KINGDOM_H