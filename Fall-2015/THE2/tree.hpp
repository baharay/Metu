#ifndef TREE_H_
#define TREE_H_
#include <cstdlib>
#include <string>
using namespace std;

class TreeNode {
 friend class Tree;
	friend class WordNet;
  string data;
  TreeNode *firstchild;
  TreeNode *nextsibling;
  TreeNode(string d = string(), TreeNode * fc = NULL,  TreeNode * ns = NULL) : data(d), firstchild(fc), nextsibling(ns) {};
};


class Tree {
	
	friend class TreeNode;
	friend class WordNet;
	TreeNode* treeroot;
	
	Tree() : treeroot(NULL){};
	TreeNode* getroot();
	void insertNode( TreeNode* node, string data);
	TreeNode* findNode(TreeNode* p, string data);

};

#endif
