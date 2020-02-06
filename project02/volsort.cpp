#include "volsort.h"

using namespace std;

bool node_number_compare(const Node *a, const Node *b)
{
	return a->number < b->number;
}

bool node_string_compare(const Node *a, const Node *b)
{
	return a->string < b->string;
}

void dump_node(Node *n)
{
    while (n != nullptr)
    {
        cout << "String = " << n->string << '\n';
        cout << "Number = " << n->number << '\n';
        n = n->next;
    }
}

void List::push_front(const string &s)
{
    Node *newnode;
	int strtoint;

	if (!(stoi(s)))
		strtoint = 0;
	else
		strtoint = stoi(s);

    newnode = new Node;

    newnode->string = s;
    newnode->number = strtoint;
    newnode->next = head;
    head = newnode;
    size++;
}
