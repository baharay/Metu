#include "NobleHouse.h"
#include "Character.h"
 NobleHouse::NobleHouse(){
 	supporterCount = 30;
	type = 1;
	duellist = NULL;
 }

  NobleHouse::NobleHouse(string neym){
  	name = neym;
 	supporterCount = 30;
	type = 1;
	duellist = NULL;
 }

 NobleHouse::~NobleHouse(){
 	delete duellist;
 }

	 void NobleHouse::assignCharacter(Character* const character, Religion religion) {
	 	duellist = character;
	 	character->setReligion(religion);

	 }
	 void NobleHouse::dismissCharacter() {
	 	duellist->setReligion(RELIGION_NONE);
	 	duellist = NULL;

	 }

	 std::string NobleHouse::getName() const {
	 	return name;
	 }
	 Character* NobleHouse:: getDuellist() const {
	 	return duellist;
	 }

	 int NobleHouse::getSupporterCount() const {
	 	return supporterCount;
	 }
	 void NobleHouse::setSupporterCount(int count) {
	 	if(count >=0 && count <= 60)
	 	supporterCount = count; 
	 }

		// Optional methods.
	 void NobleHouse::increaseSupportCount() {
	 	if(supporterCount+3 <= 60)
	 	supporterCount += 3;
	 	else supporterCount = 60 ;// ************************burayı sor
	 }
	 void NobleHouse::decreaseSupportCount() {
	 	if(supporterCount -3 >=0)
	 	supporterCount -= 3;
	 	else supporterCount = 0 ;// ************************burayı sor
	 }

	void NobleHouse::fight() {
		if (supporterCount - (supporterCount*2/10) > 0)
		{
		supporterCount -= (supporterCount*2)/10;
		}
		else supporterCount = 0;
	}	
