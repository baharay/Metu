#ifndef NOBLE_HOUSE_H
#define NOBLE_HOUSE_H

#include "House.h"

// TODO: Define Noble House Class
class NobleHouse: public House {
public:
		NobleHouse();
		NobleHouse(string neym);
		 ~NobleHouse();

		 void assignCharacter(Character* const character, Religion religion) ;
		 void dismissCharacter() ;

		 std::string getName() const ;
		 Character* getDuellist() const ;

		 int getSupporterCount() const ;
		 void setSupporterCount(int supporterCount) ;

		 void increaseSupportCount() ;
		 void decreaseSupportCount() ;

		 void fight() ;


};
#endif // NOBLE_HOUSE_H
