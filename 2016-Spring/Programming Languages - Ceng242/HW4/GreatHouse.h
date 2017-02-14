#ifndef GREAT_HOUSE_H
#define GREAT_HOUSE_H

#include "House.h"

// TODO: Define Great House Class
class GreatHouse: public House {
public:
		GreatHouse();
		GreatHouse(string neym);
		 ~GreatHouse();

		 void assignCharacter(Character* const character, Religion religion) ;
		 void dismissCharacter() ;

		 std::string getName() const ;
		 Character* getDuellist() const ;

		 int getSupporterCount() const ;
		 void setSupporterCount(int supporterCount) ;

		 void increaseSupportCount() ;
		 void decreaseSupportCount() ;

		void disappointedMatch(bool hasWon);
		void boredMatch();



};
#endif // GREAT_HOUSE_H
