#include "tree.hpp"
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;


	TreeNode* Tree::getroot(){
		return treeroot;
}


void Tree::insertNode(TreeNode* p, string data){

	TreeNode * nnode = new TreeNode(data, NULL, NULL);

	if(p->firstchild == NULL){

		p->firstchild= nnode;}
	else{

		p = p->firstchild;

		while(p->nextsibling ){

			p = p->nextsibling;}
		
		p->nextsibling = nnode;
	}


}


	TreeNode* Tree::findNode(TreeNode* p, string data){
	if(p == NULL)

		return p;

	else if((p->data).compare(data)==0)

		return p;

	else {

		TreeNode* first = findNode(p->firstchild, data);
		TreeNode* second = findNode(p->nextsibling, data);
		if(first)

			return first;
		else if(second)

			return second;	
		else
			{	
			return NULL;}
	}


}


