// generate_map.cpp
// Project 4
// Authors: Logan Tillman, Grant Anderson
// Date: March 11, 2020

/* This program takes in a number N, and generates a random NxN map of tiles */

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>  
using namespace std;

int main(int argc, char **argv)
{
	// Error checking the arguments
	if (argc != 2)
	{
		cerr << "Usage: ./generate_map <N> (will generate NxN map)\n";
		return -1;
	}
	
	map <int, char> tilecost;
	int randomnum;
	const int n = stoi(argv[1]);

	// Random time seeding
	srand (time(NULL));
	
	// Inserting possible tiles to generate
	tilecost.insert(make_pair(1, 'g'));
	tilecost.insert(make_pair(2, 'G'));
	tilecost.insert(make_pair(3, 'f'));
	tilecost.insert(make_pair(4, 'h'));
	tilecost.insert(make_pair(5, 'r'));
	tilecost.insert(make_pair(7, 'm'));

	// Outputting the initial variables
	cout << "6" << '\n';
	cout << "f 3\n" << "g 1\n" << "G 2\n" << "h 4\n" << "m 7\n" << "r 5\n"; 
	cout << n << " " << n << '\n';

	// Printing the randomly generated map
	for (int i = 0; i < (n*n); i++)
	{
		if (i % n == 0 && i != 0)
			cout << '\n';

		// Generating 6 random numbers to decide which tile to use
		randomnum = rand() % 6 + 1;
		if (randomnum == 6)
			randomnum = 7;
		
		cout << tilecost.find(randomnum)->second << " ";
	}

	// Outputting the starting and ending positions (top left, and bottom right)
	cout << "\n0 0\n";
	cout << n-1 << " " << n-1 << '\n';
return 0;
}
