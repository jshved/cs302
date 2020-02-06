// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//Implementation

void stl_sort(List &l, bool numeric) {

	vector<Node *> vec;
	Node *newnode = l.head;

	//place the nodes into a vector
	while(newnode != nullptr){
		
		vec.push_back(newnode);
		newnode = newnode->next;

	}

	//sort the vector
	if(numeric)
		sort(vec.begin(), vec.end(), node_number_compare);
	else
		sort(vec.begin(), vec.end(), node_string_compare);


	//reorder the nodes
	for(unsigned int i = 0; i < vec.size(); i++)
		vec[i]->next = vec[i+1];

	//reset head
	l.head = vec[0];

}
