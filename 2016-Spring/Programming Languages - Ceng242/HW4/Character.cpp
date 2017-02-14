#include "Character.h"
#include "Enums.h"
#include <utility>

Character::Character(string neym){
	name = neym;
}

string Character::getName() const{
	return name;
}
string Character::getAbbreviation() const{
	return abbreviation;
}

int Character::getHealth() const{
	return health;
}
int Character::getAttackPower() const{
	return attackPower;
}

int Character::getBleeding() const{
	return bleedingLevel;
}
void Character::setBleeding(int bld){
	bleedingLevel = bld;
}

int Character::getFrostBitten() const{
	return frostBittenLevel;
}
void Character::setFrostBitten(int frst){
	frostBittenLevel = frst;
}

int Character::getTakingMagicalDamage() const{
	return takingMagicalDamageLevel;
}

void Character::setTakingMagicalDamage(int mgc){
	takingMagicalDamageLevel = mgc;
}

///  It would ease your job to implement these as a function.
void Character::takeDamage(int damage){
	health -= damage;
}
void Character::applyCheerBonus(int damageBonus){
	attackPower += damageBonus;
}
//*****************************************************************
void Character::restoreOriginalValues(){
	health = healthDefault;
	attackPower = attackPowerDefault;
}

void Character::removeDebuffs(){
	bleedingLevel = 0;
	frostBittenLevel = 0;
	takingMagicalDamageLevel = 0;

}
//*********************************************************
void Character::saveOriginalValues(){
	attackPowerDefault = attackPower;
	healthDefault = health;
}

void Character::applyDOTs(){
	health -= bleedingLevel * BLEEDING_DAMAGE;
	health -= frostBittenLevel * FROSTBITE_DAMAGE;
	health -= takingMagicalDamageLevel * MAGICAL_DAMAGE;	
} 

bool Character::isDead(){
	if (health<=0)
	{
		return true;
	}
	return false;
}
///  It would ease your job to implement these as a function.

// Note: Do not implement getters for Weapon/Armor/Religion.
// Note: Weapon/Armor/Religion will buff health or/and attack power.

void Character::setWeapon(Weapon weapon){
	if(lastWeaponDamage != 0)
		attackPower -= lastWeaponDamage;
	attackPower += weaponValue(weapon); //ENUMS.CPP LAZIM MI?
	lastWeaponDamage = weaponValue(weapon);
	saveOriginalValues();
}
void Character::setArmor(Armor armor){
	if(lastArmor != 0)
		health -= lastArmor;
	health += armorValue(armor);
	lastArmor = armorValue(armor);
	saveOriginalValues();
}
void Character::setReligion(Religion religion){
	if(lastReligionAttack != 0 && lastReligionHealth != 0){
		attackPower -= lastReligionAttack;
		health -= lastReligionHealth;
	}
	attackPower += (religionValue(religion)).first;
	health += (religionValue(religion)).second;

	lastReligionAttack = (religionValue(religion)).first;
	lastReligionHealth = (religionValue(religion)).second;
	saveOriginalValues();
}
