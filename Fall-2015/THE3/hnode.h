#include <string>
using namespace std;

class hashtable;

class hnode{
friend class hashtable;
friend class DNSManager;
string ip;
string url;
string nextdns;
int accesscnt;
hashtable * table;

bool deleted;

	hnode() : ip(""), url(""), nextdns(""), accesscnt(0), table(NULL), deleted(false){};

};



