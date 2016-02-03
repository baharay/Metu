#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	typedef struct cNode {
		int data;
		struct cNode* prev;
		struct cNode* next;
		struct qNode* qHead;
	}cNode;

	typedef struct qNode {
		char data[6];
		struct qNode* prev;
		struct qNode* next;
	}qNode;


	qNode* qTable[10];


cNode * makecnode(int count)
{
	cNode * newNode;
	newNode = (cNode*) malloc(sizeof(cNode));
	newNode->data = count;
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->qHead = NULL;
	return newNode;

}

qNode * makeqnode(char word[])
{
	qNode * newNode;
	newNode = (qNode*) malloc(sizeof(qNode));

	strcpy(newNode->data, word);

	newNode->next = NULL;
	newNode->prev = NULL;

	return newNode;

}

void insertcNode (cNode **headRef, int count)
{
	cNode * np;
	if((np = makecnode(count)))
		{ 
		cNode* curr, *prev;
		curr=*headRef;
		prev = NULL;
		
		
				
		while(curr && count>(curr->data))
			{
			prev = curr;
			curr = curr->next;
			}

		if(curr &&( count==(curr->data)))
			{			
			return;
			}

		else
			{
			np->next=curr;
			np->prev=prev;
			if(prev)
				prev->next=np;
			
			else
				*headRef=np;

			if(curr)
				curr->prev = np;
			return;
			}
		}

}

void insertqNode(cNode** headRef, int count, char word[6], int i)
{
	cNode * cnp;
	qNode * np;
	cnp = *headRef;
	while(count!=(cnp->data))
		cnp = cnp->next;
	if((np = makeqnode(word)))
		{
		qTable[i] = np;
		if (cnp->qHead == NULL)
			{	
			cnp->qHead = np;
			return;
			}
		else
			{
			qNode* curr, *prev;
			curr=cnp->qHead;
			prev = NULL;

			while(curr && strcmp(word,curr->data)>0 )
				{
				prev = curr;
				curr = curr->next;
				}


			np->next=curr;
			np->prev=prev;
			if(prev)
				{
				prev->next=np;
				if(curr)
					curr->prev=np;
				return;
				}
			else	
				{
				cnp->qHead=np;
				if(curr)
					curr->prev=np;
				return;
				}
		
			}

		}

}

void showNodes(cNode** head, FILE * op)
{
	cNode* curr;
	qNode* now;
	curr =  *head;	

	while(curr!=NULL)
	{
		now = curr->qHead;
		fprintf(op,"%d", curr->data );
		while(now!=NULL)
		{
			fprintf(op," %s", now->data );

			now = now->next;
		}
		fprintf(op,"\n");		
		curr = curr->next;
		
	}
	
}

int checkspace()
{	
	int filled=0,i;
	for (i=0; i<10;i++)
		{
		if(qTable[i] !=NULL)
		filled++;
		}
	if(filled <10)
		return 1;
	else
		return 0;
}

int checkexist(char word[])
{
	int i;
	for (i=0; i<10;i++)
		{
		if(qTable[i]!= NULL && strcmp(qTable[i]->data,word)==0)
			return 1;
		}
	return 0;

}

int findcount(cNode** headRef, char word[])
{
	int count=0;
	cNode* curr;
	qNode* qcurr;
	curr=*headRef;
	while(curr)
		{
		count = curr->data;
			
		qcurr = curr->qHead;
		while(qcurr)
			{
			if(strcmp(qcurr->data,word)==0)
				return count;
			qcurr= qcurr->next;

			}
			
		curr= curr->next;
		}		
	return count;
}


int whereexist(char word[])
{
	int i;
	for (i=0; i<10;i++)
		{
		if(qTable[i]!= NULL && strcmp(qTable[i]->data,word)==0)
	
		return i;
		}
	return i;
}


void deleteqNode(cNode** headRef, int count, char word[])
{
	cNode * cnp;
	qNode* curr, *prev;
	cnp = *headRef;


	while( count!=(cnp->data))
		{
		cnp = cnp->next;
		}	
	

	curr=cnp->qHead;
	prev = NULL;
	
	if(curr && (strcmp(curr->data,word)==0))
		{
			cnp->qHead = curr->next;
			if(curr->next)
				curr->next->prev = NULL;
			return;
		}

	while(curr && (strcmp(word,curr->data)!=0))
				{
				prev = curr;
				curr = curr->next;
				}
	
	if(prev)
		{
		prev->next=curr->next;
		if(curr->next)
			curr->next->prev=prev;
		return;
		}
			
}

void deletecNode(cNode** headRef, int count)
{
	cNode * curr;
	cNode *prev;
	prev = NULL;

	curr = *headRef;

	while(curr && count!=(curr->data))
		{
		prev = curr;
		curr = curr->next;
		}	
	

	if(curr &&curr->qHead==NULL)
		{
		if(prev)
			{
			if(curr->next)
				curr->next->prev=prev;
			prev->next=curr->next;
			return;
			}
		else
			*headRef=curr->next;
			if(curr->next)
				curr->next->prev=prev;			
			return;
		}	
}


int emptyslot()
{
	int i;
	for (i=0; i<10;i++)
		{
		if(qTable[i] == NULL)
		return i;
		}
	return i;
}


int main()
{

	cNode* head =NULL;
	cNode** headRef;
	char ch[6];
	int count;
	int n, i;
	char word[6];
	FILE * fp;
	FILE * op;

	headRef=&head;

	fp = fopen("input.txt", "r");
	for(i=0;i<10;i++)
		qTable[i]=NULL;
	
	
	fscanf(fp," %d", &n);

	for(i=0;i<n;i++)
	{
	
	fscanf(fp,"%s", word);
	fscanf(fp,"%d", &count);

	insertcNode(headRef, count);
	insertqNode(headRef,count,word,i);

	}

	
	while(fscanf(fp,"%s",ch) != EOF)
	{

		if(checkspace() && !checkexist(ch))
		{
			insertcNode(headRef, 1);
			insertqNode(headRef,1,ch,emptyslot());
		}
		else if( checkexist(ch))
		{
			
			count = findcount(headRef, ch);

			insertcNode(headRef, count+1);
			insertqNode(headRef,count+1,ch,whereexist(ch));
	
			deleteqNode(headRef, count, ch);
			deletecNode(headRef, count);
		}
		else if( (checkexist(ch)==0) && (checkspace()==0))
		{
			int emptyspace;
			emptyspace=whereexist(head->qHead->data);

			deleteqNode(headRef, head->data, head->qHead->data);
			deletecNode(headRef, head->data);
		
			insertcNode(headRef, 1);
			insertqNode(headRef,1,ch,emptyspace);

		}

	}
fclose(fp);
op = fopen("output.txt", "w");
showNodes(headRef,op);
fclose(op);	
return 0;
}
