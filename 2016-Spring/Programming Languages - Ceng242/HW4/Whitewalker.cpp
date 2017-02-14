#include "Whitewalker.h"


Whitewalker::Whitewalker (string characterName) : Character ( characterName) {
//	name = characterName;
	abbreviation = "-WHI-";
	attackPower = 40;
	health = 600;
	attackPowerDefault = 40;
	healthDefault = 600;
	bleedingLevel = 0;
	frostBittenLevel = 0;
	takingMagicalDamageLevel = 0;

	lastWeaponDamage=0;
	lastArmor=0;
	lastReligionAttack=0;
	lastReligionHealth=0;
}
	


void Whitewalker::attackTo(Character* const character){
	if(character->getFrostBitten() <3 ){

	character->setFrostBitten(character->getFrostBitten()+1);		
	}
	
	character->takeDamage(attackPower);



}
