// quick.cpp

/* This is an attempted implementation of quicksort using a singly linked list.
   This function will give a segfault when you run it. It seems like implementing
   quicksort with a singly linked list is a terrible idea, and the skeleton code for 
   this function just doesn't work. */

#include "volsort.h"

#include <iostream>

// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric) 
{
	// Helper function for qsort
	l.head = qsort(l.head, numeric);
}

Node *qsort(Node *head, bool numeric) 
{
	// Base case
	if (head->next == nullptr)
		return head;

	Node *left;
	Node *right;

	// Calling partition with the head as the pivot
	partition(head, head, left, right, numeric);

	// Calling qsort recursively on the left and right sides
	qsort(left, numeric);
	qsort(right, numeric);
	
	// Concatenating the left and right side
	return concatenate(left, right);	
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) 
{
	Node *newleft;
	Node *newright;
	Node *newhead;

	// Using this for my comparison
	newhead = head;

	while (newhead != nullptr)
	{	
		// If comparing numbers
		if (numeric == true)
		{
			// If the newhead is less than pivot, insert on left
			if (node_number_compare(newhead, pivot) == true)
			{
				if (left == nullptr)
				{
					left = newhead;
					
					// Using newleft as a placeholder for the head of left
					newleft = left;
					left = left->next;
				}
				else
				{
					left = newhead;
					left = left->next;
				}
			}
			// If the newhead is greater than the pivot, insert on the right
			else if (node_number_compare(newhead, pivot) == false)
			{
				if (right == nullptr)
				{
					right = newhead;

					// Using newright as a placeholder for the head of right
					newright = right;
					right = right->next;
				}
				else
				{
					right = newhead;
					right = right->next;
				}
			}
		}

		// If comparing strings
		else if (numeric == false)
		{
			// If the newhead is less than the pivot, insert on the left
			if (node_string_compare(newhead, pivot) == true)
			{
				if (left == nullptr)
				{	
					left = newhead;
					newleft = left;
					left = left->next;
				}
				else
				{
					left = newhead;
					left = left->next;
				}
			}
			// If the newhead is greater than the pivot, insert on the right
			else if (node_string_compare(newhead, pivot) == false)
			{
				if (right == nullptr)
				{
					right = newhead;
					newright = right;
					right = right->next;
				}
				else
				{
					right = newhead;
					right = right->next;
				}
			}
		}

		// Increment to the next element on the list for comparison
		newhead = newhead->next;	
	}
	
	// Adding the pivot to the end of the left list
	left = pivot;

	// Adding the nullptr to the end of left and right
	left = left->next;
	left = nullptr;
	right = nullptr;

	// Restoring left and right to point to the beginning of the list	
	left = newleft;
	right = newright;
}

// Combines the two sides into one sorted list
Node *concatenate(Node *left, Node *right) 
{
	Node *head;

	// Setting head to the beginning of left
	head = left;

	// Navigates to the end of left
	while (left->next != nullptr)
		left = left->next;

	// Combines the two lists
	left->next = right;

	// Returns the head of the list
	return head;
}

