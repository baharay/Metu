#ifndef WN_H_
#define WN_H_
#include "tree.hpp"
#include <string>
using namespace std;


class WordNet{

  public:
	WordNet() : root(NULL){};
	void BuildWordNet(string);
	void HandleTask(string);
	void PrintWordNet(TreeNode *p, int depth);
	void PrintSubclasses(TreeNode *p, string);
	void PrintSuperclasses(TreeNode *p, string);
	void PrintIntermediateClasses(TreeNode *p, string, string);
	string findpath(TreeNode *p,TreeNode *q, string);
  private:
	Tree *root;

};

#endif
