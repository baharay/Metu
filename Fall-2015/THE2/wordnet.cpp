 #include <iostream>
#include <fstream>
#include <queue>
#include "wordnet.hpp"
#include "tree.hpp"
using namespace std;

void WordNet::BuildWordNet(string str){
    
	ifstream wordfile;
	wordfile.open(str.c_str());
	string word; 

	wordfile >> word;
	Tree* tr = new Tree();
	TreeNode * nnode = new TreeNode(word, NULL, NULL);
	tr->treeroot = nnode;
	this->root = tr;

    while (wordfile >> word ){
	string child; 
	string parent; 
	child = word;  

	wordfile >> parent;
	wordfile >> parent;

	struct TreeNode * tobeinserted = tr->findNode(tr->treeroot,parent);
	tr->insertNode(tobeinserted, child);
    }

}

void WordNet::PrintWordNet(TreeNode *p, int depth){

	for(int i = 0; i<depth; i++)
		cout<<"  ";
	cout<< p->data<<endl;
	if(p->firstchild != NULL)
		PrintWordNet(p->firstchild, depth+1);
	if(p->nextsibling != NULL)
		PrintWordNet(p->nextsibling, depth);
}


void WordNet::PrintSubclasses(Tree::TreeNode *p, string data){

	queue<TreeNode*> Q;
	p = root->findNode(p, data);
	cout<< p->data << endl;
	if(p->firstchild) Q.push(p->firstchild);

	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		cout<< p->data << endl;
		if(p->firstchild != NULL) Q.push(p->firstchild);

		while(p!=NULL && p->nextsibling !=NULL){
			cout<<p->nextsibling->data<<endl;
			if(p->nextsibling->firstchild!=NULL ) Q.push(p->nextsibling->firstchild);
			p = p->nextsibling;

		}

	}
	
}


string WordNet::findpath(TreeNode *q,TreeNode *p, string path){

	if(q == NULL)

		return "";

	else if((q->data).compare(p->data)==0)

		return q->data+" < "+path;

	else {

		string first = findpath(q->firstchild, p, q->data+" < "+path);
		string second = findpath(q->nextsibling, p, path);
		if(first.compare("")!=0)
			return first;
		else if(second.compare("")!=0)
			return second;	
		else	
			return "";
	}
}

void WordNet::PrintSuperclasses(TreeNode *p,string data){
	p = root->findNode(p, data);
	TreeNode *q = root->treeroot;
	string path = findpath(q,p,"");

	int size = path.size();
	path.resize(size-3);
	cout <<path<<endl;

}

void WordNet::PrintIntermediateClasses(TreeNode *p,string bottom, string top){
	TreeNode *q = root->findNode(p, top);
	p = root->findNode(p, bottom);
	string path = findpath(q,p,"");

	int size = path.size();
	path.resize(size-3);
	cout <<path<<endl;

}


    void WordNet::HandleTask(string str){
	string first, second, third;
	int spc1, spc2;
 	spc1 = str.find(" ");
	first = str.substr(0,spc1);
	str.erase(0,spc1+1);
 	spc2 = str.find(" ");
	second = str.substr(0,spc2);
	if(spc2!=-1){
		str.erase(0,spc2+1);
		third = str;
	}
	
	if(!first.compare("PrintWordNet")){
		
			PrintWordNet(this->root->treeroot, 0);
	}
	else if(!first.compare("PrintSubclasses")){
		
			PrintSubclasses(this->root->treeroot, second);
	}
	else if(!first.compare("PrintSuperclasses")){
		
			PrintSuperclasses(this->root->treeroot, second);
	}
	else if(!first.compare("PrintIntermediateClasses")){
		
			PrintIntermediateClasses(this->root->treeroot, second, third);
	}

}
