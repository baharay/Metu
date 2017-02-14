#ifndef WIZARD_H
#define WIZARD_H

#include "Character.h"

// TODO: Define Wizard Class


class Wizard: public Character {
public:
	Wizard (string characterName);	
    	~Wizard(){}
 	void attackTo(Character* const character);


};
#endif // WIZARD_H
