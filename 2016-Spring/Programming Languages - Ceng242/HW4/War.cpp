#include "War.h"
#include "GreatHouse.h"
#include "NobleHouse.h"
#include <vector>
#include <utility>
#include <iostream>
using namespace std;
		void War::startSimulation(){
			int  winner, winnerpoints=0;
			int k = 1, count=1;
			std::vector<Kingdom *> winners (kingdomCount());
			cout<< "War has started with "<< kingdomCount() << " kingdoms."<<endl;

		for ( k = 1; k < kingdomCount(); ++k)
			{

			for (int i = 0; i+k < kingdomCount(); ++i)
			{			cout<<"---------------"<<endl;
				cout<< "Duel "<< count<<": "<< v[i]->getName()<<" vs " << v[i+k]->getName() <<endl;
				winner = duelOfKingdoms(v[i], v[i+k]);
				if (winner == 1)
				{//cout<<"winner1"<<endl;
					v[i]->increaseDuelPoints();
					cout << endl<<"The winner is: " << v[i]->getName() << " with currently "<< v[i]->getDuelPoints() <<" kingdom points."<<endl;
					cout<<"---------------"<<endl;
				}
				else if (winner == -1)
				{//cout<<"winner2"<<endl;
					v[i+k]->increaseDuelPoints();
					cout << endl<<"The winner is: " << v[i+k]->getName() << " with currently "<< v[i+k]->getDuelPoints() <<" kingdom points."<<endl;
					cout<<"---------------"<<endl;

				}
				else{//cout<<"winner0"<<endl;
					v[i]->increaseDuelPoints();
					v[i+k]->increaseDuelPoints();
					cout<< endl <<"A draw."<<endl;
					cout<<"---------------"<<endl;
				}

				count++;
			}

			}


		for (unsigned int i = 0; i < v.size(); ++i)
		{
			if (v[i]->getDuelPoints() > winnerpoints )
			{
				winnerpoints = v[i]->getDuelPoints();
				winners.clear();
				winners.push_back(v[i]);
			}
			else if (v[i]->getDuelPoints() == winnerpoints)
			{
				winners.push_back(v[i]);
			}

		}
			
			if (winners.size() > 1)
			{
				//cout<< endl;				

				cout<< "The War is over. The new owners of King's Landing are ";
				for (unsigned int i = 0; i < winners.size()-1; ++i)
				{
					cout << winners[i]->getName() << ", ";
				}
				cout << "and " << winners[winners.size()-1]->getName() <<"."<<endl;
			}
			else{
				//cout<< endl;

				cout << "The War is over. The new owner of King's Landing is "<<  winners[0]->getName() << " with a total of "<< winnerpoints <<" points."<<endl;
			}
			cout<<endl;



			for (unsigned int i = 0; i < v.size(); ++i)
			{
				delete v[i];
			}
		}

		// The return value should go accordingly:
		// 1 -> First Kingdom/House/Character won.
		// 0 -> Draw.
		// -1 -> Second Kingdom/House/Character won.

		int War::duelOfKingdoms(Kingdom* kingdom1, Kingdom* kingdom2){ // BURADA SORUN VAR LOOPLARDA
			int winner, dpk1=0, dpk2=0;
			unsigned int count = 0, k=0, j=0, tour =0;

			count = 9;

			for (unsigned int i = 0; i < count; ++i)
			{

					winner = duelOfHouses((kingdom1->getNobleHouses())[j], (kingdom2->getNobleHouses())[k]);
					if(winner ==1){						
							dpk1++;
					}
					else if (winner==-1)
					{					
							dpk2++;
					}

					k++;
					if (k == 3)
					{
						k=0;

					}
					j++;
					if (j== 3)
					{
						j =0;
						tour++;
						k = tour;
					}


			}



			winner = duelOfHouses(kingdom1->getGreatHouse() , kingdom2->getGreatHouse());
					
					if(winner ==1){						
							dpk1+=3;
					}
					else if (winner==-1)
					{					
							dpk2+=3;
					}

			cout<< "  "<<kingdom1->getName() <<  " got " << dpk1 << " house points. ";
			cout<<kingdom2->getName() <<  " got " << dpk2 << " house points."<<endl;
			if (dpk1 > dpk2)
			{


				return 1;		
			}
			else if (dpk2 > dpk1)
			{
	

				return -1;	
			}
			else
			{

				return 0;
			}

		}
		int War::duelOfHouses(House* house1, House* house2){
			std::pair <int,int> tmp;
			int duelval=0, roundcount=0;

			cout << "  Duel between " << house1->getName()<<"("<< house1 -> getSupporterCount() <<") "<< house1->getDuellist()->getAbbreviation()<<" and " << house2->getName()<<"("<< house2 -> getSupporterCount()<<") "<< house2->getDuellist()->getAbbreviation()<<" has begun."<<endl;

			if (house1->type == 0) // GREAT HOUSE
			{
				tmp = duelOfCharacters(house1->getDuellist(), house2->getDuellist(), house1->getSupporterCount(), house2->getSupporterCount());
				duelval = (tmp).first;
				roundcount = (tmp).second;

				if (roundcount<=2)
				{
					if(duelval == 1){
					house1->disappointedMatch(1);
					house2->disappointedMatch(0);

					}
					else if (duelval == -1)
					{
					house1->disappointedMatch(0);
					house2->disappointedMatch(-1);

					}
					

				}
				if (roundcount>6)
				{
					house1->boredMatch();
					house2->boredMatch();	
				}
				if (duelval==1)
				{
					house1->increaseSupportCount();
					house2->decreaseSupportCount();
					//cout<< "house1 won"<<endl;
				}
				else if (duelval == -1)
				{

					house2->increaseSupportCount();
					house1->decreaseSupportCount();
					//cout<< "house2 won"<<endl;
				}
				

			}
			else{

				tmp = duelOfCharacters(house1->getDuellist(), house2->getDuellist(), house1->getSupporterCount(), house2->getSupporterCount());
				duelval = (tmp).first;
				roundcount = (tmp).second;
				if (duelval ==1 && house2->getSupporterCount() > house1->getSupporterCount())
				{
					house1->fight();
				}
				else if (duelval ==-1 && house1->getSupporterCount() > house2->getSupporterCount())
				{
					house2->fight();
				}
				if (duelval==1)
				{
					house1->increaseSupportCount();
					house2->decreaseSupportCount();
				//	cout<< "house1 won"<<endl;
					return duelval;
				}
				else if (duelval == -1)
				{

					house2->increaseSupportCount();
					house1->decreaseSupportCount();
//cout<< "house2 won"<<endl;
					return duelval;

				}				


			}
		//	cout<< "house draw"<<endl;
			return duelval;
		}


		

		// First part -> Duel Value
		// Second part -> Round Count
		pair<int, int> War::duelOfCharacters(Character* character1, Character* character2, int cheerBonus1, int cheerBonus2){
			character1->restoreOriginalValues();
			character2->restoreOriginalValues();

			character1->removeDebuffs();
			character2->removeDebuffs();

			character1->applyCheerBonus(cheerBonus1);
			character2->applyCheerBonus(cheerBonus2); 

			int duelround = 0, tmphealth = 0, tmp1, tmp2;
			while(!character1->isDead() && !character2->isDead() ){
				tmphealth = character1->getHealth();
				tmp1 = character1 ->getHealth();
				tmp2 = character2 -> getHealth();
				character1->applyDOTs();
				if (character1 ->getHealth() < tmphealth )
				{
					cout << "    "<<character1->getName()<<"(" << tmp1 <<")"<< " took " << tmphealth - character1->getHealth() << " damage as DOT." <<endl;
				}
				tmphealth = character2 ->getHealth();
				character2->applyDOTs();
				if (character2 ->getHealth() < tmphealth )
				{
					cout << "    "<<character2->getName()<<"("<< tmp2 <<")"<< " took " << tmphealth - character2->getHealth() << " damage as DOT." << endl;
				}

				tmp1 = character1 ->getHealth();
				tmp2 = character2 -> getHealth();

				character1->attackTo(character2);
				cout << "    "<<character1->getName() <<"("<< character1->getHealth() <<")" << " hit " << character2->getName()<<"("<< tmp2 <<") " << character1->getAttackPower()<<"."<<endl;
				character2->attackTo(character1);
				cout << "    "<<character2->getName()<<"("<< character2->getHealth () <<")" << " hit " << character1->getName() <<"("<< tmp1 <<") "<< character2->getAttackPower()<<"."<<endl;
				
				cout<<"    "<<"****"<<endl;
				duelround++;
			}
			if (!character1->isDead() && character2->isDead())
			{
				cout << "    "<<character1->getName() <<"("<< character1->getHealth() <<")"<< " has won."<< endl;
				return make_pair(1, duelround); //1ST DUELLIST WON
			}
			else if (character1->isDead() && !character2->isDead()){
				cout << "    "<<character2->getName()<<"("<< character2->getHealth() <<")" << " has won." <<endl;
		
				return make_pair(-1, duelround); //2ND DUELLIST WON
			}
			else
				cout << "    Both of them are dead. A draw." << endl;
		
				return make_pair(0,duelround); //DRAW
		}
	
		//--//

		// You are free to add/change methods below. These example methods are for your own convenience.
		void War::addKingdom(Kingdom* kingdom){
			v.push_back(kingdom);
		}
		void War::removeKingdom(Kingdom* kingdom){
			for (unsigned int i = 0; i < v.size(); ++i)
			{
				if (v[i] == kingdom)
				{
					v.erase(v.begin()+i);
					break;
				}
			}
		}

		int War::kingdomCount(){
			return v.size();
		}

