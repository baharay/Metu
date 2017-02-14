#ifndef HOUSE_H
#define HOUSE_H

#include "Character.h"

#include <vector>

class House 
{	
	public:
		virtual ~House(){} ;

		virtual void assignCharacter(Character* const character, Religion religion) = 0;
		virtual void dismissCharacter() = 0;

		virtual std::string getName() const = 0;
		virtual Character* getDuellist() const = 0;

		virtual int getSupporterCount() const = 0;
		virtual void setSupporterCount(int supporterCount) = 0;

		// Optional methods.
		virtual void increaseSupportCount() = 0;
		virtual void decreaseSupportCount() = 0;

		virtual void disappointedMatch(bool hasWon) {}		// Applies only for Great Houses.
		virtual void boredMatch() {}						// Applies only for Great Houses.

		virtual void fight() {}								// Applies only for Noble Houses.
		// Optional methods.
		int type; // 0 for great house, 1 for noble house 	
	protected:
    	std::string name;
    	Character* duellist;

    	int supporterCount;

};

#endif // HOUSE_H
