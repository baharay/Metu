#include "Wildling.h"

Wildling::Wildling (string name): Character(name) {
	//name = characterName;
	abbreviation = "-WIL-";
	attackPower = 70;
	health = 425;
	attackPowerDefault = 70;
	healthDefault = 425;
	bleedingLevel = 0;
	frostBittenLevel = 0;
	takingMagicalDamageLevel = 0;

	lastWeaponDamage=0;
	lastArmor=0;
	lastReligionAttack=0;
	lastReligionHealth=0;
}


void Wildling::attackTo(Character* const character){
	if(character->getBleeding() <3 ){

	character->setBleeding(character->getBleeding()+1);		
	}
	
	character->takeDamage(attackPower);



}
