#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <cstdlib>
#include "LinkedNode.h"

template<class T>
class LinkedList {
private:
	LinkedNode<T> *head;
	LinkedNode<T> *tail;	
public:
    /* Default constructor. Initialize member variables. */ 
	LinkedList() : head(NULL), tail(NULL){};
	
	/* Default destructor. Free all the memory used. */
	~LinkedList();//
	
	/* Returns head of the linked list. */
	LinkedNode<T>* getHead() const;
	
	/* Returns tail of the linked list. */
	LinkedNode<T>* getTail() const;
	
	/* Returns idx-th node of the linked list under 0-based numbering.
	 */
	LinkedNode<T>* getNodeAt(int idx) const;
	
	/* Inserts a new node containing _data_ at the beginning of the linked list.
	 */
	void insertFirst(T &data);	
	
	/* Inserts a new node containing _data_ after _node_.
	 */
	void insertNode(LinkedNode<T>* node, T &data);
		
	/* Deletes _node_ from the linked list
	 */
	void deleteNode(LinkedNode<T>* node);
};


template <class T>
	  LinkedList<T>::~LinkedList() {
		LinkedNode<T>* tmp = getHead();
		while(tmp->getNext())
		{
		
			deleteNode(tmp);
			tmp= head;
		}
		delete head;
		delete tail;
}

template <class T>
	  LinkedNode<T>* LinkedList<T>::getHead() const{
		return head;
}

template <class T>
	  LinkedNode<T>* LinkedList<T>::getTail() const{
		return tail;
}

template <class T>
	LinkedNode<T>* LinkedList<T>::getNodeAt(int idx) const{
		
		LinkedNode<T>* tmp = head;
		for(int i=1; i<idx+1; i++)
		{tmp = tmp->getNext();}
		return tmp;

}

template <class T>
	void LinkedList<T>::insertFirst(T &data){
		LinkedNode<T>* newNode = new LinkedNode<T>(NULL,NULL,data);
		if(head==NULL)
		{
			head = newNode;
		}
		else
		{
			LinkedNode<T>* tmp = head->getNext();
			tmp->setPrev(newNode);
			head = newNode;
			newNode->setNext(tmp);
		}

}

template <class T>
	void LinkedList<T>::insertNode(LinkedNode<T>* node, T &data){
		LinkedNode<T>* newNode = new LinkedNode<T>(node,node->getNext(),data);
		if(node->getNext())
		{
			LinkedNode<T>* tmp = node->getNext();
			tmp->setPrev(newNode);
		}

		node->setNext(newNode);
	
}

template <class T>
	void LinkedList<T>::deleteNode(LinkedNode<T>* node){
		
		if(node->getNext())
		{
			LinkedNode<T>* tmp = node->getNext();
			tmp->setPrev(node->getPrev());		
		}
		LinkedNode<T>* tmp2 = node->getPrev();
		if(tmp2!=NULL){		
			tmp2->setNext(node->getNext());
		}	
		else
		{
		head=node->getNext();
		}	
}




#endif
