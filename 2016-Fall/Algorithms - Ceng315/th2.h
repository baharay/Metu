#include <string>


class Node {
 public:

 	int rank;
	int name;
bool isFinal;
    Node * parent;

Node();
Node(int name);




} ;



std::string dfa_equality(std::string file1, std::string file2);
void link(Node * x, Node * y);
void union1(Node * x, Node * y);
Node * find_set(Node  x);
