// Challenge 05: Graph Paths
// Author: Logan Tillman
// Date: February 21, 2020

/* This program takes in a series of graphs specified by edge pairs, then a series of paths to check for.
   It completes this task by storing the graphs in a map, then traversing the map using a DFS Traversal */

#include <iostream>
#include <map>
#include <vector>
using namespace std;

// Main Execution

// Determines if the path exists by using recursion
void find(const map <char, vector<char>> &matrix, vector<int> &visited, const char &start, const char &target, bool &found);

int main(int argc, char *argv[]) {
	map < char, vector<char> > matrix;
	vector <int> visited;
	unsigned int nedges, npaths, graph;
	char one, two;

	// Initializing which graph we're looking at (for printing purposes)
	graph = 1;

	// Reading in all graphs one at a time
	while(cin >> nedges)
	{
		// Used for printing a newline (just formatting)
		if (graph > 1)
			cout << '\n';

		// Adding the graph paths to the map
		for (unsigned int i = 0; i < nedges; i++)
		{
			cin >> one >> two;
			matrix[one].push_back(two);
		}

		cin >> npaths;

		// Checking to see if the paths exist for the graph
		for (unsigned int i = 0; i < npaths; i++)
		{
			bool found;

			// Initializing variables to avoid errors
			found = false;
			visited.resize(1, 0);

			cin >> one >> two;

			// Calling the intial find function
			find(matrix, visited, one, two, found);

			if (found == true)
			{
				cout << "In Graph " << graph << " there is a path from " 
					 << one << " to " << two << '\n';			
			}
			else
			{
				cout << "In Graph " << graph << " there is no path from " 
					 << one << " to " << two << '\n';			
			}

			// Clearing the visited vector for re-use
			visited.clear();
		}
		
		// Clearing the matrix and incrementing the graph count
		graph++;
		matrix.clear();
	}

  return (0);
}

// Recursive function to determine if the path exists in the graph
void find(const map <char, vector<char>> &matrix, vector<int> &visited, const char &start, const char &target, bool &found)
{
	// Base cases
	if (found == true)
		return;

	// Checking to see if we've already visited a node
	if (visited.size()-1 >= (unsigned int) start-65)
	{
		if (visited[start-65] == -1)
			return;
	}

	map <char, vector<char>>::const_iterator mit;

	mit = matrix.find(start);

	if (mit != matrix.end())
	{
		// Checking to see if the path exists under the current node
		for (unsigned int i = 0; i < mit->second.size(); i++)
		{
			if (mit->second[i] == target)
				found = true;
		}

		// Resizing the visited vector if needed
		if (visited.size() <= (unsigned int) start-65)
			visited.resize(start-64, 0);

		// Setting the current node to visited
		visited[start-65] = -1;

		// Recursively calling itself with every child of the current node
		for (unsigned int i = 0; i < mit->second.size(); i++)
			find(matrix, visited, mit->second[i], target, found);	
	}
}
