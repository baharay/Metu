#ifndef WHITEWALKER_H
#define WHITEWALKER_H

#include "Character.h"

// TODO: Define Whitewalker Class
class Whitewalker : public Character {
public:
	Whitewalker (string characterName);	
    	~Whitewalker(){}
 	void attackTo(Character* const character);


};
#endif // WHITEWALKER_H
