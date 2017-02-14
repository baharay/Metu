#ifndef WILDLING_H
#define WILDLING_H

#include "Character.h"

// TODO: Define Wildling Class
class Wildling: public Character {
public:
	Wildling (string characterName);	
    	~Wildling(){}
 	void attackTo(Character* const character);


};
#endif // WILDLING_H
