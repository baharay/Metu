#include "GreatHouse.h"
#include "Character.h"
 GreatHouse::GreatHouse(){
 	supporterCount = 50;
 	type = 0;
 	duellist = NULL;
 }

 GreatHouse::GreatHouse(string neym){
 	name = neym;
 	supporterCount = 50;
 	type = 0;
 	duellist = NULL;
 }

 GreatHouse::~GreatHouse(){
 	delete duellist;
 }

	 void GreatHouse::assignCharacter(Character* const character, Religion religion) {
	 	duellist = character;
	 	character->setReligion(religion);

	 }
	 void GreatHouse::dismissCharacter() {
	 	duellist->setReligion(RELIGION_NONE);
	 	duellist = NULL;

	 }

	 std::string GreatHouse::getName() const {
	 	return name;
	 }
	 Character*GreatHouse:: getDuellist() const {
	 	return duellist;
	 }

	 int GreatHouse::getSupporterCount() const {
	 	return supporterCount;
	 }
	 void GreatHouse::setSupporterCount(int count) {
	 	if(count >=0 && count <= 100)
	 	supporterCount = count; 
	 }

		// Optional methods.
	 void GreatHouse::increaseSupportCount() {
	 	if(supporterCount+5 <= 100)
	 	supporterCount += 5;
	 	else supporterCount = 100 ; //************************burayı sor
	 }
	 void GreatHouse::decreaseSupportCount() {
	 	if(supporterCount -5 >=0)
	 	supporterCount -= 5;
	 	else supporterCount = 0 ; //************************burayı sor
	 }

	 void GreatHouse::disappointedMatch(bool hasWon) {
	 	if(hasWon==0) //LOSE
	 	 supporterCount -8 >= 0 ? supporterCount -=8 : supporterCount = 0;

	 	else if (hasWon==1)
	 	 supporterCount +4 <= 100 ? supporterCount += 4 : supporterCount = 100; //WIN
	 	// hasWon == -1 DRAW

	 }		// Applies only for Great Houses.
	 void GreatHouse::boredMatch() {
	 	if(supporterCount -6 >=0)
	 	supporterCount -= 6;
	 	else supporterCount = 0 ; //************************burayı sor
	 }						// Applies only for Great Houses.

