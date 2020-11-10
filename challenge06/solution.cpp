// Challenge 7: Minimum Spanning Tree
// CS302
// Author: Logan Tillman
// Date: March 7, 2020

/* This program will determine the minimum spanning tree for an undirected graph given through standard input */

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

// Main Execution

int main(int argc, char *argv[]) {
	multimap <int, vector<int>> initmap;
	multimap <int, vector<int>> crossing;
	set <pair <int, int>> mst;
	set <int> nodes;
	multimap <int, vector<int>>::const_iterator init_iterator;
	set <pair <int, int>>::const_iterator mst_iterator;
	set <int>::const_iterator nodes_iterator;
	vector <vector <int>> matrix;
	vector <int> connected;
	int nvertices, num, totalweight, count;

	count = 0;
	totalweight = 0;

	// Executes for each graph
	while (cin >> nvertices)
	{
		matrix.resize(nvertices);
	
		// This is just used for output formatting
		if (count != 0)
			cout << '\n';

		// Creating the matrix of the graph
		for (int i = 0; i < (nvertices*nvertices); i++)
		{
			cin >> num;
			matrix[i%nvertices].push_back(num);
		}

		// Adding the existing edges to the initial multimap
		for (unsigned int i = 0; i < matrix.size(); i++)
		{
			for (unsigned int j = 0; j < matrix[0].size(); j++)
			{
				if (matrix[i][j] != -1)
				{
					connected.push_back(i);
					connected.push_back(j);
					initmap.insert(make_pair(matrix[i][j], connected));
					connected.clear();
				}
			}
		}

		// Always starting at node A
		nodes.insert(0);

		// Looping through each currently connected node
		while (mst.size() != (unsigned) nvertices-1)
		{
			bool foundnodes;

			foundnodes = false;
			
			// Finding a candidate to be added to the MST
			for (nodes_iterator = nodes.begin(); nodes_iterator != nodes.end(); nodes_iterator++)
			{
				for (init_iterator = initmap.begin(); init_iterator != initmap.end(); init_iterator++)
				{
					if (init_iterator->second[0] == *nodes_iterator)
					{
						if (nodes.find(init_iterator->second[1]) == nodes.end())
						{
							foundnodes = true;
							crossing.insert(make_pair(init_iterator->first, init_iterator->second));
						}
					}
				}
			}

			// If we found potential nodes to be inserted
			if (foundnodes == true)
			{
				// Increase the weight of our MST
				totalweight += crossing.begin()->first;

				// Insert the pair into our MST set
				if (crossing.begin()->second[0] < crossing.begin()->second[1])
					mst.insert(make_pair(crossing.begin()->second[0], crossing.begin()->second[1]));
				else
					mst.insert(make_pair(crossing.begin()->second[1], crossing.begin()->second[0]));

				// Add the newly found node to the nodes set
				nodes.insert(crossing.begin()->second[1]);
			}

			// Clearing the candidate multimap
			crossing.clear();
		}

		cout << totalweight << '\n';
		for (mst_iterator = mst.begin(); mst_iterator != mst.end(); mst_iterator++)
			cout << (char) (mst_iterator->first+65) << (char) (mst_iterator->second+65) << '\n';

		// Clearing variables for next graph
		count++;
		totalweight = 0;
		nodes.clear();
		matrix.clear();
		initmap.clear();
		connected.clear();
		mst.clear();
	}
  return (0);

}

