// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <array>
#include <iostream>
#include <vector>

using namespace std;

//Prototypes
int compare_str(const void * n1, const void * n2);
int compare_num(const void * n1, const void * n2);

//Implementation
void qsort_sort(List &l, bool numeric) {

	vector<Node *> vec;
	Node *newnode = l.head;

	//create vector of nodes
	while(newnode != nullptr){

		vec.push_back(newnode);
		newnode = newnode->next;

	}

	//sort vectors
	if(numeric)
		qsort(&vec[0], vec.size(), sizeof(vec[0]), compare_num);
	else
		qsort(&vec[0], vec.size(), sizeof(vec[0]), compare_str);

	//reorder nodes
	for(unsigned int i = 0; i < vec.size(); i++)
		vec[i]->next = vec[i+1];

	//reset head
	l.head = vec[0];

}

int compare_num(const void * n1, const void * n2){

	//typecast void * to Node *
	Node *a = *(struct Node **) n1;
	Node *b = *(struct Node **) n2;

	//comparisons
	if(a->number < b->number)
		return -1;
	else if(a->number > b->number)
		return 1;

	//if equals
	return 0;
}

int compare_str(const void * p1, const void * p2){

	//typecast
	Node *a = *(struct Node **)p1;
	Node *b = *(struct Node **)p2;

	//comparisons
	if(a->string < b->string)
		return -1;
	else if(a->string > b->string)
		return 1;

	//if equal
	return 0;
}

