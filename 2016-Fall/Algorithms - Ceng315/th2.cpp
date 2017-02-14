#include "th2.h"
#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <fstream>
#include <utility>  
#include <algorithm>
#include <sstream>
#include <new>

using namespace std;


Node::Node () {
	name = 0;

 	rank = 0;
 	isFinal = 0;
 	parent = 0;
}

Node::Node (int name) {
	this->name = name;
    parent = this;
 	rank = 0;
 	isFinal = 0;
}



void link(Node *x, Node *y){
    if (x->rank > y->rank)
        y->parent = x;
    else
        x->parent = y;
    if (x->rank == y->rank)
        y->rank++;
    

}

Node * find_set(Node *x){
    cout << " x "<< x->name  <<"  "<<endl;
    if (x->parent->name != x->name)
    {
        //cout <<" x: "<< x << " px before: " << p[x]<<endl;
        x->parent = find_set(x->parent);
    //    //cout <<" x: "<< x << " px after: " << p[x]<<endl;       
    }
    ////cout <<"rito";
    return x->parent;
}

void union1(Node *x, Node *y){

    link(find_set(x), find_set(y));

}


void lol(){};



void get_input(string filename, int * num_of_states, int * num_of_symbols, int * start_state, vector<int> *final_states,    vector< vector<int> > *transitions){
    ifstream file;

    file.open (filename.c_str());
    if (!file.is_open()) return;  

    string snum_of_states, snum_of_symbols,sstart_state;
    string word;

    file >> snum_of_states ;
    *num_of_states = atoi(snum_of_states.c_str());
    //cout <<* num_of_states << endl;
 


    file >> snum_of_symbols;
    *num_of_symbols = atoi(snum_of_symbols.c_str());
    //cout << num_of_symbols << endl;
    file >> sstart_state;
    *start_state = atoi(sstart_state.c_str());
    //cout << start_state <<endl;

    getline (file,word);
    //cout << word  << "word";
    getline (file,word);
    //cout << word  << "word";

    istringstream iss(word);

    do{
        string sub;
        iss >> sub;
        if (!sub.empty())
        {final_states->push_back(atoi(sub.c_str()));
            //cout  << sub <<" fin " << atoi(sub.c_str())<<endl;   
             }    
    }
    while (iss);

    transitions->resize(*num_of_states);
    for (int i = 0; i < *num_of_states; ++i)
    {
        for (int j = 0; j < *num_of_symbols; ++j)
        {
            file >> word;
            (*transitions)[i].push_back(atoi(word.c_str()));
            //cout << i << j <<" " << atoi(word.c_str())<<endl;
        }
    }
    file.close();


}

string dfa_equality(string file1, string file2){

    int num_of_states1, num_of_symbols1, start_state1, num_of_states2, num_of_symbols2, start_state2;
    vector<int> final_states1; 
    vector<int> final_states2; 
////cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";//cout <<"voy";
    vector< vector<int> > transitions1 ;
    get_input(file1, &num_of_states1, &num_of_symbols1, &start_state1, &final_states1,&transitions1);
    vector< vector<int> > transitions2 ;
    get_input(file2, &num_of_states2, &num_of_symbols2, &start_state2, &final_states2,&transitions2);
    int size = num_of_states1+num_of_states2;
   int n = num_of_states1;
    transitions1.resize(size);
    stack< Node * > s;


    Node * arr = new Node[size];


    for (int i = 0; i < size; ++i)
    {
        arr[i] = Node(i);

    }



    for (int i = 0; i < num_of_states2; ++i)
    {

        final_states2[i] += n;
        for (int j = 0; j < num_of_symbols2; ++j)
        {
            transitions1[i+n].push_back(transitions2[i][j] + n);

        }

    }

    for (int i = 0; i < final_states1.size(); ++i)
    {
    	arr[final_states1[i]].isFinal = 1;
    }
    for (int i = 0; i < final_states2.size(); ++i)
    {
    	arr[final_states2[i]].isFinal = 1;
    }

    Node * i1 = (Node * ) &arr[start_state1];
    Node * i2 = (Node * ) &arr[start_state2+n];    

    s.push(i2);
    s.push(i1);
    union1((Node * ) &arr[start_state1],(Node * ) &arr[start_state2+n]);

    Node  t1,t2;
   Node * r1 ;
   Node * r2 ;
    while(s.size() != 0){
                        //cout << "6 ";
        Node* temp1 = s.top();
                        //cout << "7 ";
        s.pop();
        Node* temp2 = s.top();
                        //cout << "7 ";
        s.pop();
        //cout << "00000000000 "<<temp.first <<" "<< temp.second <<" "<<n << endl;
        for (int i = 0; i < num_of_symbols1; ++i)
        {

        	
            r1 = find_set(&arr[transitions1[temp1->name][i]]); 
          
            r2 = find_set(&arr[transitions1[temp2->name][i]]);
           cout << "**" << r1->name << r2->name <<endl ;
            if (r1->name != r2->name ){
               //cout << "1 ";
                union1(r1,r2);
                //cout << "2 ";
                
                //cout << "3 ";
                s.push(r2);  
                                s.push(r1);             
                //cout << "4 ";
            }         
            //cout << "5 ";
//cout << s.size();
         }

                
    }
lol();

    for (int i = 0; i < size; ++i)
    {
    	for (int j = 0; j < size; ++j)
    	{


    				cout <<i<<" " <<arr[i].parent->name<< endl;
    				cout <<j<< " "<<arr[j].parent->name<< endl;
    			/*if(arr[i].parent->name == arr[j].parent->name){
    				cout <<i<< arr[i].parent->name<< endl;
    				cout <<j<< arr[j].parent->name<< endl;
    				if (arr[i].isFinal && (!arr[j].isFinal))

    				{
    					return "notequal\n";
    				}
    				if ((!arr[i].isFinal) && arr[j].isFinal)
    				{
    					return "notequal\n";
    				}

    			}
	    		 */
    	}
    }
    return "equal\n";


}