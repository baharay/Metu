#include "Kingdom.h"
		Kingdom::Kingdom(string kingdomName, Religion kingdomReligion){
			name = kingdomName;
			religion = kingdomReligion;
			duelPoints = 0;
			totalDuelCount = 0;
			greatHouse = NULL;

            std::vector<House *> temp (3); //doğru mu
            nobleHouses = temp;

		}
    	Kingdom::~Kingdom() {

                delete greatHouse;


                for (int j = 0; j < 3; ++j)
                {


                    delete nobleHouses[j];
                }

    	}

    	void Kingdom::assignGreatHouse(House* const grt) {
    		greatHouse = grt;
            if(greatHouse ->getDuellist() != NULL)
    		greatHouse->getDuellist()->setReligion(religion); // EMİN DEĞİLİM
    	}
    	void Kingdom::dismissGreatHouse() {

            if(greatHouse ->getDuellist() != NULL)
    		greatHouse->getDuellist()->setReligion(RELIGION_NONE); // EMİN DEĞİLİM
    		greatHouse = NULL;
    	}

    	void Kingdom::addNobleHouse(House* const nobleHouse) {
            if(nobleHouse ->getDuellist() != NULL)
     		nobleHouse->getDuellist()->setReligion(religion); // EMİN DEĞİLİM   

    		if(nobleHouses[0] == 0)
    			nobleHouses[0] = nobleHouse;
    		else if (nobleHouses[1] == 0)
    			nobleHouses[1] = nobleHouse;
    		else
    			nobleHouses[2] = nobleHouse;

    	}
    	void Kingdom::removeNobleHouse(House* const nobleHouse) {
            if(nobleHouse ->getDuellist() != NULL)

     		nobleHouse->getDuellist()->setReligion(RELIGION_NONE); // EMİN DEĞİLİM   		
    		if(nobleHouses[0] == nobleHouse)
    			nobleHouses[0] = NULL;
    		else if (nobleHouses[1] == nobleHouse)
    			nobleHouses[1] = NULL;
    		else
    			nobleHouses[2] = NULL;


    	}

        string Kingdom::getName() {
        	return name;

        }
        Religion Kingdom::getReligion() {
        	return religion;

        }

        void Kingdom::setReligion(Religion r) {
        	religion = r;

        }
        
    	House* Kingdom::getGreatHouse() {
    		return greatHouse;

    	}
    	vector <House *> Kingdom::getNobleHouses() {
    		return nobleHouses;

    	}

        // Optional methods.
        void Kingdom::increaseDuelPoints() {
        	duelPoints++;

        }
        void Kingdom::increaseTotalDuelCount() {
        	totalDuelCount++;

        }

        int Kingdom::getTotalDuelCount() {
        	return totalDuelCount;

        }
        int Kingdom::getDuelPoints() {
        	return duelPoints;

        }
        // Optional methods
