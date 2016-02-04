#ifndef __DNSManager_h__
#define __DNSManager_h__

#include <string>
#include <vector>
#include "hash.h"

using namespace std;
// YOU ARE EXPECTED TO IMPLEMENT THE CLASS BELOW AS WELL AS
// ANY OTHER NECESSARY CLASS (SUCH AS THE HASH TABLE CLASS) AND 
// AUXILIARY STRUCTURES THAT YOU NEED.


class DNSManager
{
    public:
        // DO NOT MODIFY ANYTHING IN THE PUBLIC PART. WHEN TESTING YOUR
        // CODES, WE WILL OVERWRITE THE PUBLIC PART WITH WHAT IS GIVEN
        // IN THIS FILE. ANY MODIFICATIONS THAT YOU MAKE WILL BE LOST.

        DNSManager();

        void registerDNS(const std::string& dnsIP);
        
        void deleteDNS(const std::string& dnsIP);

        void registerURL(const std::string& url,
                         const std::string& ip,
                         const std::vector<std::string>& dnsChain);

        void deleteURL(const std::string& url);

        std::string access(const std::string& url,
                           int& accessCount,
                           int& hopCount);

        void mergeDNS(const std::string& dnsIP1, 
                      const std::string& dnsIP2);

    private:
	friend class hashtable;
	friend class hnode;
	hashtable * DNStable;
	string masterdns;
        // YOU MAY FREELY MODIFY THE PRIVATE PART OF THIS CLASS

	
};

	DNSManager::DNSManager(){
		DNStable = new hashtable();
		masterdns ="";
	}


        void DNSManager::registerURL(const std::string& url, const std::string& ip, const std::vector<std::string>& dnsChain){

		unsigned int i = 0;

		for(i=0; i< dnsChain.size(); i++)
		{
			int hashval = DNStable->hash(dnsChain[i]);
			hashtable * curdns = DNStable->kek[hashval].table;
			hashval = curdns->hash(url);
			int pos = curdns->findempty(url);
			if(pos==-1)
				return;
			else{
				curdns->kek[pos].ip=ip;
				curdns->kek[pos].url=url;
				curdns->kek[pos].deleted= false;
				curdns->kek[pos].table= NULL;
				if((i+1)<dnsChain.size())
					curdns->kek[pos].nextdns= dnsChain[i+1];
				else
					curdns->kek[pos].nextdns="";
				curdns->elements++;
				curdns->updateload();
		
				if(curdns->loadf>=0.5)
					curdns->rehash();
			}
		}
	}

        void DNSManager::registerDNS(const std::string& dnsIP){
		if(DNStable->loadf>=0.5)
			DNStable->rehash();

		if(masterdns=="")
		{
			masterdns= dnsIP;
		}

		int pos = DNStable->findempty(dnsIP);
		if(pos==-1)
			return;
		
		else if((dnsIP) != (DNStable->kek[pos].ip))
		{
			DNStable->kek[pos].ip= dnsIP;
			DNStable->kek[pos].url= dnsIP;
			DNStable->kek[pos].deleted= false;
			DNStable->kek[pos].table= new hashtable();
			DNStable->elements++;
			DNStable->updateload();
		
		}			

	}		

        std::string DNSManager::access(const std::string& url, int& accessCount,int& hopCount){
		if(masterdns=="")
			return "not found";
		int hop = 1;
		int hashval = DNStable->find(masterdns);
		hashtable * curdns = DNStable->kek[hashval].table;
		if((DNStable->kek[hashval].deleted == true))
			return "not found";

		hashval = curdns->hash(url); 
		int pos = curdns->find(url);
		if(pos==-1) return "not found";

		if(curdns->kek[pos].nextdns ==""){
			curdns->kek[pos].accesscnt++;
			accessCount = curdns->kek[pos].accesscnt;
			hopCount = hop;
			return curdns->kek[pos].ip;
		}
		else{
			while(curdns->kek[pos].nextdns !=""){
				hop++;		
				hashval = DNStable->hash(curdns->kek[pos].nextdns);

				if((DNStable->kek[hashval].deleted == true)||DNStable->kek[hashval].ip=="" )
					return "not found";
				curdns = DNStable->kek[hashval].table;


				pos = curdns->find(url);
			

				if(pos == -1) return "not found";
				if((curdns->kek[pos].nextdns) ==""){
					curdns->kek[pos].accesscnt++;
					accessCount = curdns->kek[pos].accesscnt;
					hopCount = hop;
					return curdns->kek[pos].ip;
				}

			}
			return "not found";
		}	

	}

        void DNSManager::deleteDNS(const std::string& dnsIP){
	if(dnsIP == masterdns)
		masterdns ="";

		int pos = DNStable->find(dnsIP);
		DNStable->kek[pos].deleted = true;
		DNStable->elements--;
		DNStable->updateload();


}


        void DNSManager::deleteURL(const std::string& url){

		int hashval = DNStable->hash(masterdns);
		hashtable * curdns = DNStable->kek[hashval].table;
 
		int pos = curdns->find(url);
		curdns->kek[pos].deleted = true;
		curdns->elements--;
		curdns->updateload();
}


        void DNSManager::mergeDNS(const std::string& dnsIP1,const std::string& dnsIP2){
		int pos1 = DNStable->find(dnsIP1);
		int pos2 = DNStable->find(dnsIP2);

		if((pos1 == -1) || (pos2==-1))
		return;

	hashtable * curdns1 = DNStable->kek[pos1].table;
	hashtable * curdns2 = DNStable->kek[pos2].table;

	if((DNStable->kek[pos1].deleted == true) || (DNStable->kek[pos2].deleted == true)) return;
	int nsize = (curdns1->elements + curdns2->elements)*2;
	nsize = curdns1->nextprime(nsize);
	int nprime = curdns1->nextprime(nsize/20);

	hnode* ntable = new hnode[nsize];

	for(int i=0; i<curdns1->tablesize; i++){
		if((curdns1->kek[i].ip != "")&&(curdns1->kek[i].deleted == false)){
			hnode hp = curdns1->kek[i];
			int hashval = curdns1->mergehash(hp.url, nsize, nprime);
			int k=0;
		
			if(ntable[hashval].ip !=""){
				while(ntable[hashval].ip !="")
					{
					hashval = (hashval + 2*k + 1)%nsize;
					k++;}
			}
			ntable[hashval]= hp;
		}
	}
	for(int i=0; i<curdns2->tablesize; i++){
		if((curdns2->kek[i].ip != "")&&(curdns2->kek[i].deleted == false)){
			hnode hp = curdns2->kek[i];
			int hashval = curdns2->mergehash(hp.url, nsize, nprime);
			int k=0;
		
			if(ntable[hashval].ip == curdns2->kek[i].ip ){
								
				ntable[hashval]= hp;
				if(dnsIP1 == curdns2->kek[i].nextdns )
				ntable[hashval].nextdns = "";
			
			}
			else if(ntable[hashval].ip !=""){

				if(dnsIP1 == curdns2->kek[i].nextdns )
				ntable[hashval].nextdns = "";
			
				while(ntable[hashval].ip !="")
				{	hashval = (hashval + 2*k + 1)%nsize;
					k++;
					if(ntable[hashval].ip == curdns2->kek[i].ip )break;
				}

			}

			ntable[hashval]= hp;
		}
	}
	curdns1->elements = curdns1->elements + curdns2->elements;
	curdns1->tablesize = nsize;
	curdns1->updateload();
	curdns1->prime=nprime;
	delete[] curdns1->kek;
	deleteDNS(dnsIP2);
	curdns1->kek = ntable;
	
}


#endif // __DNSManager_h__
