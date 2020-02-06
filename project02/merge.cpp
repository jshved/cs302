// merge.cpp
// References: https://www.quora.com/What-is-a-slow-pointer-and-a-fast-pointer-in-a-linked-list (provided in lab write up)
//
//start
#include "volsort.h"
#include <iostream>
using namespace std;
// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
	msort(l.head, numeric);
}

Node *msort(Node *head, bool numeric) {
	//Base cases
	//If there is one element just return
	if(head == nullptr || head->next == nullptr)
		return head;

	Node *left;
	Node *right;

	split(head, left, right);

	msort(left,  numeric);
	msort(right, numeric);

	return merge(left,right, numeric);

}

void split(Node *head, Node *&left, Node *&right) {
	Node *slow_ptr, *fast_ptr;
	slow_ptr = head;
	fast_ptr = head;

	if(head == nullptr) return;

	//Use fast and slow pointer technique to find the end and middle of the list
	while(fast_ptr->next != nullptr && fast_ptr->next->next != nullptr)  //From quora.com. See reference above
	{
		slow_ptr = slow_ptr->next;
		fast_ptr = fast_ptr->next->next;
	}

	//Split the list in half

	//Create left sublist
	left = head;
	//Create right sublist
	right = slow_ptr->next;

	//"cut off" the left list from the other half
	slow_ptr->next = nullptr;

}

Node *merge(Node *left, Node *right, bool numeric) {


	Node *head, *tmp;
	
	//Create the head node
	head = new Node();

	//Start with the head node and build the new list
	for(tmp = head; left != nullptr && right != nullptr; tmp = tmp->next)
	{
		if(numeric == true)
		{
			if(node_number_compare(left,right) == true)
			{
				tmp->next = left;
				left = left->next;
			}
			else
			{
				tmp->next = right;
				right = right->next;
			}
		}

		else if (numeric == false)
		{
			if(node_string_compare(left,right) == true)
			{
				tmp->next = left;
				left = left->next;
			}
			else
			{
				tmp->next  = right;
				right = right-> next;
			}
		}
	}


	//Get back to the start of the list
	if(left == nullptr) tmp->next = right;
	else tmp->next = left;
	return tmp;
}

