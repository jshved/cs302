// dijsktras.cpp
// Project 4
// Authors: Logan Tillman, Grant Anderson
// Date: March 11, 2020

/* This program will take a graph through standard input, along with a starting point and ending point.
   It will use Dijkstras algorithm to create the shortest path between the two points. */

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <ctype.h>
using namespace std;

// Used to store our Node Information
struct Node
{
	Node(int ind, char t, int w);
	Node *backedge;
	bool visited;
	char tile;
	int distance;
	int index;
	int weight;
	vector <Node *> adjacent;
};

// Used to store information about our graph
struct Matrix
{
	public:
		Matrix(unsigned int numtiles);
		~Matrix();
		void CreatePath();
		void FindEdges();
	private:
		unsigned int rows, cols;
		unsigned int start, end;
		vector <Node *> graph;
		map <char, int> tilecosts;
		map <char, int>::const_iterator tileiterator;
};

// Main Execution
int main(int argc, char *argv[]) 
{
	unsigned int numtiles;

	cin >> numtiles;

	// Creating the graph
	Matrix landscape(numtiles);

	landscape.FindEdges();
	landscape.CreatePath();

	return 0;
}

// Node Constructor
Node::Node(int ind, char t, int w)
{
	backedge = NULL;
	visited = 0;
	tile = t;
	distance = -1;
	index = ind;
	adjacent.resize(0);
	weight = w;
}

// Matrix Constructor
Matrix::Matrix(unsigned int numtiles)
{
	char tilename, inputtile;
	unsigned int startrow, startcol, endrow, endcol;
	int tilecost;
	int weight;

	// Reading in tile costs
	for (unsigned int i = 0; i < numtiles; i++)
	{
		cin >> tilename >> tilecost;
		tilecosts[tilename] = tilecost;
	}

	cin >> rows >> cols;

	// Creating the graph of nodes
	for (unsigned int i = 0; i < (rows * cols); i++)
	{
		Node *inputnode;

		cin >> inputtile;
		tileiterator = tilecosts.find(inputtile);
		weight = tileiterator->second;
		inputnode = new Node(i, inputtile, weight);
		graph.push_back(inputnode);

	}

	// Setting the adjacent vectors of each node
	for (int i = 0; i < (int) graph.size(); i++)
	{
		// Adding above node to adj
		if ((i-cols) >= 0 && (i-cols) < (rows*cols))
			graph[i]->adjacent.push_back(graph[i-cols]);

		// Adding left node to adj
		if (((i%cols)-1 >= 0) && (i%cols)-1 < (rows*cols))
			graph[i]->adjacent.push_back(graph[i-1]);

		// Adding right node to adj
		if (((i%cols)+1 < cols) && (i%cols)+1 < (rows*cols))
			graph[i]->adjacent.push_back(graph[i+1]);

		// Adding below node to adj
		if ((i+cols) < (rows*cols))
			graph[i]->adjacent.push_back(graph[i+cols]);
	}

	cin >> startrow >> startcol >> endrow >> endcol;

	// Converting the start/end rows and cols to fit our 1d vector format
	end = (endrow*rows)+endcol;
	start = (startcol*rows)+startcol;
}

// Destructor
Matrix::~Matrix()
{
	// Deleting all of the nodes in the graph
	for (unsigned int i = 0; i < graph.size(); i++)
		delete graph[i];
}

// Finding the edges in the graph
void Matrix::FindEdges()
{
    multimap<int, Node *> Nodes;
    multimap<int, Node *>::iterator nit;
	Node *n;

	// Initializing the first node
    graph[0]->distance = 0;
    n = graph[0];

	// Inserting it into the multimap
    Nodes.insert(pair<int, Node *>(n->distance, n));

    while(!Nodes.empty())
	{
		int dist;

        nit = Nodes.begin();
        nit->second->visited = true;
        dist = nit->second->distance;

		// Looping through all adjacent nodes
        for(unsigned int j = 0; j < nit->second->adjacent.size(); j++)
		{
			// If the node hasn't been visited
            if(nit->second->adjacent[j]->visited == false)
			{
				// If the node's weight < its distance (or if its distance is -1)
                if((dist+nit->second->adjacent[j]->weight) < nit->second->adjacent[j]->distance || 
				   (nit->second->adjacent[j]->distance == -1))
				{
					int a;
					
					// Updating its distance
                    nit->second->adjacent[j]->distance = dist + nit->second->adjacent[j]->weight;

					// Setting its backedge
                    nit->second->adjacent[j]->backedge = nit->second;

					// Inserting the node into the multimap
                    a = nit->second->adjacent[j]->index;
                    Nodes.insert(pair<int, Node *>(nit->second->adjacent[j]->distance, graph[a]));
                }
            }
        }

        nit = Nodes.begin();
        Nodes.erase(nit);
    }
}

// Constructing the shortest path between the start and end
void Matrix::CreatePath()
{
    vector<int> flow;
    int totalWeight;
    Node *n;

	// Starting at the ending node
    n = graph[end];
	totalWeight = 0;

	// Calculating the total distance and putting all of the path nodes into a vector
    while(true)
    {
        if (n->index != (int) end)
            totalWeight += n->weight;

        flow.push_back(n->index);

        if (n->index == (int) start)
            break;
        else
            n = n->backedge;
    }

	// Output formatting
    cout << totalWeight << '\n';

    for(int i = flow.size()-1; i >= 0; i--)
        cout << flow[i]/cols << ' ' << flow[i]%cols << '\n';

}
