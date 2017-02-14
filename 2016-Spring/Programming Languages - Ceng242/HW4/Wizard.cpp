#include "Wizard.h"

Wizard::Wizard (string characterName): Character ( characterName) {
//	name = characterName;
	abbreviation = "-WIZ-";
	attackPower = 60;
	health = 450;
	attackPowerDefault = 60;
	healthDefault = 450;
	bleedingLevel = 0;
	frostBittenLevel = 0;
	takingMagicalDamageLevel = 0;

	lastWeaponDamage=0;
	lastArmor=0;
	lastReligionAttack=0;
	lastReligionHealth=0;

}


void Wizard::attackTo(Character* const character){
	if(character->getTakingMagicalDamage() <3 ){

	character->setTakingMagicalDamage(character->getTakingMagicalDamage()+1);		
	}
	
	character->takeDamage(attackPower);


}
