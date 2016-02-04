#include <string>
#include "hnode.h"
#include <cmath>

using namespace std;


//class hnode;

class hashtable{
friend class hnode;
friend class DNSManager;
float loadf;
float elements;
int prime;
int tablesize;
hnode* kek;

	hashtable() : loadf(0), elements(0), prime(7), tablesize(61){
	kek = new hnode[tablesize];};

	int hash(string word);
	float updateload();
	void rehash();
	int nextprime(int number);
	int find(string word);
	int findempty(string word);
	int mergehash(string word, int size, int prime);
}; 


int hashtable::hash(string word){
	int hashval=0;
	for(unsigned int i=0; i<word.length(); i++)
		hashval= word[i]+ hashval*this->prime;
	hashval = hashval%tablesize;
	if(hashval<0)
		hashval+=tablesize;
	return hashval;

}

int hashtable::mergehash(string word, int size, int prime){
	int hashval=0;
	for(unsigned int i=0; i<word.length(); i++)
		hashval= word[i]+ hashval*prime;
	hashval = hashval%size;
	if(hashval<0)
		hashval+=size;
	return hashval;

}

float hashtable::updateload(){
	loadf = elements/tablesize;
	return loadf;
}

int hashtable::nextprime(int number){

int smallnumber = 2;
number = number*2+1;
	while(smallnumber<sqrt(number)){

	if(number%smallnumber==0)
		{number++;
		smallnumber =2;}
	else smallnumber++;
	}
	return number;

}

int hashtable::find(string word){

	int hashval = hash(word);
	if((this->kek[hashval].url == word))
		return hashval;
	else{
		int h1 = hashval;
		int i=0;
		while((kek[hashval].url) != word){
			hashval = (hashval + 2*i + 1)%tablesize;
			i++;

			if(kek[hashval].url=="")
				return -1;
			else if((kek[hashval].url == word)&&(kek[hashval].deleted== false))
				return hashval;

			else if(h1 == hashval)
				return -1;

		}
		if(kek[hashval].deleted== false)
			return hashval;
		else
			return -1;
	}
}

int hashtable::findempty(string word){

	int hashval = hash(word);
	if((this->kek[hashval].url == word)&& ((kek[hashval].deleted)== false))
		return -1;
	if((this->kek[hashval].ip =="")||(kek[hashval].deleted== true))
		return hashval;
	else{
		int i=0;
		while((kek[hashval].ip != "")&&(kek[hashval].deleted== false)){
			hashval = (hashval + 2*i + 1)%tablesize;
			i++;
		}
		return hashval;
	}
}

void hashtable::rehash(){
	if(prime<(tablesize/10))
		prime = nextprime(prime);
	int old = tablesize;
	tablesize = nextprime(tablesize);
	hnode* ntable = new hnode[tablesize];

	for(int i=0; i<old; i++){
		if((kek[i].ip != "")&&(kek[i].deleted == false)){
			hnode hp = this->kek[i];
			int hashval = this->hash(hp.url);
			int k=0;
		
			if(ntable[hashval].ip !=""){
				while(ntable[hashval].ip !="")
					{hashval = (hashval + 2*k + 1)%tablesize;
					k++;}
			}
			ntable[hashval]= hp;
		}
	}
	delete[] kek;
	this->kek = ntable;
	
		
}

