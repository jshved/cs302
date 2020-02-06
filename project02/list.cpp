#include "volsort.h"

// Not sure if this is right... Feel free to change this if you figure it out
List::List() 
{
	head = new Node;
	head = nullptr;
//	head->next = nullptr;
	size = 0;
}

List::~List() 
{
	delete head;
}
