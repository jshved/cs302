// Challenge 08: Adding List-Based Integers
// solution.cpp
// Author: Logan Tillman
// Date: March 27, 2020

/* This program will add List-Based integers through a custom implementation of a linked list*/

#include <iostream>
using namespace std;

// Templated node type
template<typename T>
class Node 
{
 public:
  Node(const T &);     
  T getData() const;   

  T data;           
  Node<T> *next;    
};

// Templated linked list class
template<typename T>
class LinkedList 
{
 public:
  LinkedList();    
  ~LinkedList();

  bool empty();                 
  void print();                 
  void clear();
  void push_front(const T &info);
  size_t size;

  // First element in the list
  Node<T> *first;             
  // Creates a new node
  Node<T> *newNode(const T &);
};

// Function for adding two lists
template<typename T>
void AddLists (const LinkedList<T> &list1, const LinkedList<T> &list2);

int main(int argc, char *argv[]) 
{
	LinkedList<int> list1;
	LinkedList<int> list2;
	string str1, str2;

	// Reading the integers as strings
	while (cin >> str1 >> str2)
	{
		// Adding the strings to the linked lists
		for (unsigned int i = 0; i < str1.size(); i++)
			list1.push_front(str1[i]-48);
		for (unsigned int i = 0; i < str2.size(); i++)
			list2.push_front(str2[i]-48);
		
		// Adding the lists together
		AddLists<int>(list1, list2);

		// Clearing the lists
		list1.clear();
		list2.clear();
	}

    return 0;
}

// Constructor, using member initialization list syntax
template<typename T>
Node<T>::Node(const T &info) :data(info),next(NULL) {}

// Simple get function for our class (if friendship is not used)
template<typename T>
T Node<T>::getData(void) const { return data; }

// Constructor (empty body)
template<typename T>
LinkedList<T>::LinkedList() :first(NULL) 
{
	size = 0;
}

// Destructor (clears the linked list)
template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

// Checks to see if the list is empty
template<typename T>
bool LinkedList<T>::empty()
{ 
	return (first == NULL); 
}

// Utility function to create a node
template<typename T>
Node<T> *LinkedList<T>::newNode(const T &value) 
{
	return new Node<T>(value);
}

// Prints the contents of the list
template<typename T>
void LinkedList<T>::print()
{
	Node<T> *p=first;

	for( ; p != NULL; p = p->next)
		cout << p->getData();

	cout << endl;
}

// Clears all information out of the list
template<typename T>
void LinkedList<T>::clear()
{
	Node<T> *temp;

	while (empty() == false)
	{
		temp = first->next;
		delete first;
		first = temp;
		size--;
	}
}

// Adds a node to the front of the list
template <typename T>
void LinkedList<T>::push_front(const T &info)
{
	Node<T> *newnode;

	newnode = newNode(info);
	newnode->data = info;
	newnode->next = first;
	first = newnode;
	size++;
}

// Adds two lists together
template <typename T>
void AddLists (const LinkedList<T> &list1, const LinkedList<T> &list2)
{
	LinkedList<int> rv;
	Node<T> *one;
	Node<T> *two;
	int carry, temp;

	// Initializing variables
	temp = 0;
	carry = 0;
	one = list1.first;
	two = list2.first;

	while (one != NULL || two != NULL)
	{
		// Adding the element in the first list if it's not NULL
		if (one != NULL)
		{
			temp += one->getData();
			one = one->next;
		}

		// Adding the element in the second list if it's not NULL
		if (two != NULL)
		{
			temp += two->getData();
			two = two->next;
		}

		// Adding the carry to the elements from the list
		temp += carry;

		// Calculating the new carry
		carry = temp / 10;

		// Putting the sum into the list
		rv.push_front(temp % 10);

		// Resetting the temporary sum
		temp = 0;

		// Accounts for the final carry (if both lists end)
		if (one == NULL && two == NULL)
			if (carry > 0)
				rv.push_front(carry);
	}

	// Prints the list
	rv.print();
}
