// sb-play.cpp
// project03
// Author: Logan Tillman
// Date: February 26, 2020

/* This is a program that plays the game Superball. It will give either a SWAP or SCORE command
   through standard output. */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <map>
#include "disjoint.h"
using namespace std;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Superball {
  public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
};

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-play rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}

// This function will analyze the board and determine the sets that are scoreable
void analyze_superball(DisjointSet *&ds, Superball *&s, map <int, int> &possiblescores, vector <int> &occurances);

// This function checks to see if a swap with the element above is possible
void checktop(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);

// This function checks to see if a swap with the element on the left is possible
void checkleft(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);

// This function checks to see if a swap with the element on the right is possible
void checkright(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);

// This function checks to see if a swap with the element below is possible
void checkbottom(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);

// This function will swap two random cells if no swap has been performed already
void swaprandom(DisjointSet *&ds, Superball *&s, unsigned int &swap1, unsigned int &swap2);

int main(int argc, char **argv)
{
    Superball *s;
    DisjointSet *ds;
	map <int, int> possiblescores;
	map <int, int>::const_iterator pit;
    vector <int> occurances;
	vector <int> vertices;
	int maxpoints, location, maxlength;

    s = new Superball(argc, argv);
    ds = new DisjointSetByRankWPC (s->r*s->c);

	// Analyzing the board to determine scoring sets
	analyze_superball(ds, s, possiblescores, occurances);

	// If there are possible scores, this will execute
	if (possiblescores.empty() == false)
	{
		maxpoints = possiblescores.begin()->second;
		location = possiblescores.begin()->first;

		// Find the scoring set with the maximum points and save its location
		for (pit = possiblescores.begin(); pit != possiblescores.end(); pit++)
		{
			if (pit->second > maxpoints)
			{
				maxpoints = pit->second;
				location = pit->first;
			}
		}

		// Score the set
		cout << "SCORE " << location/s->c << " " << location%s->c << '\n';
	}

	// If there aren't any possible scores
	else
	{
		unsigned int swap1, swap2;
		maxlength = occurances[0];
		location = 0;
		swap1 = 0;
		swap2 = 1;

		// Find the longest set of connected nodes
		for (unsigned int i = 0; i < occurances.size(); i++)
		{
			if (occurances[i] > maxlength)
			{
				maxlength = occurances[i];
				location = i;
			}
		}

		// Save the location of all vertices inside the set of blocks
		for (unsigned int i = 0; i < s->board.size(); i++)
		{
			if (ds->Find(i) == location)
				vertices.push_back(i);
		}

		// Loop through each vertex
		for (int i = 0; i < (int) vertices.size(); i++)
		{
			// If the vertex is on left side of graph and a swap hasn't been performed
			if (((vertices[i] % s->c) / (s->c / 2)) == 0)
			{
				// Check to see if the element to the left is available to swap. If so, do it.
				if (swap1 == 0 && swap2 == 1)
					checkleft(ds, s, vertices[i], swap1, swap2);
			}

			// If the vertex is on the right side of the graph and still no swap has been made
			else
			{
				// Try to swap with the element on the right
				if (swap1 == 0 && swap2 == 1)
					checkright(ds, s, vertices[i], swap1, swap2);
			}

			// Still, if no swap has been made, then it tries to swap with the element above, then the element below
			if (swap1 == 0 && swap2 == 1)
				checktop(ds, s, vertices[i], swap1, swap2);

			if (swap1 == 0 && swap2 == 1)
				checkbottom(ds, s, vertices[i], swap1, swap2);
		}

		// After all the attempts for each vertex, if no swap has been made, it swaps two random cells
		if (swap1 == 0 && swap2 == 1)
			swaprandom(ds, s, swap1, swap2);

		cout << "SWAP " << swap1/s->c << " " << swap1%s->c << " " << swap2/s->c << " " << swap2%s->c << '\n';
	}

}

// This function determines the sets available to be scored
void analyze_superball(DisjointSet *&ds, Superball *&s, map <int, int> &possiblescores, vector <int> &occurances)
{
    int cells;

    cells = s->r * s->c;
    occurances.resize(cells, 0);

	// Looping through each cell on the board
    for (int i = 0; i < cells; i++)
    {
        int top, left, right, bottom;

        top = i - s->c;
        left = i % s->c - 1;
        right = i % s->c + 1;
        bottom = i + s->c;

		// Checks to see if the top exists, and is available for union
        if (top >= 0)
        {
            if (s->board[top] == s->board[i] && s->board[i] > 96)
            {
                if (ds->Find(top) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(top));
            }
        }

		// Checks to see if the bottom exists and is available for union
        if (bottom < cells)
        {
            if (s->board[bottom] == s->board[i] && s->board[i] > 96)
            {
                if(ds->Find(bottom) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(bottom));
            }
        }

		// Checks to see if the left exists and is available for union
        if (left >= 0)
        {
            if (s->board[i-1] == s->board[i] && s->board[i] > 96)
            {
                if (ds->Find(i-1) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(i-1));
            }
        }

		// Checks to see if the right exists and is available for union
        if (right < s->c)
        {
            if (s->board[i+1] == s->board[i] && s->board[i] > 96)
            {
                if (ds->Find(i+1) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(i+1));
            }
        }
    }

	// Finds the size of each color group
    for (int i = 0; i < cells; i++)
	{
		if (s->board[i] > 96)
			occurances[ds->Find(i)]++;
	}

	// Looping through each color group
    for (unsigned int i = 0; i < occurances.size(); i++)
    {
		// Determining if the size is great enough to be scored
        if (occurances[i] >= s->mss)
        {
			// If the size is great enough, it checks to see if one of the elements falls within a goal
            for (unsigned int j = 0; j < s->goals.size(); j++)
            {
				// Stores the value if a score is possible
                if (s->goals[j] == 1 && ds->Find(j) == i)
                {
                    possiblescores[j] = occurances[i];
                    break;
                }
            }
        }
    }
}

// Checks to see if a swap with the element above is valid
void checktop(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	// Making sure the top element exists
	if (i-s->c >= 0)
    {
		// Checking to see if there's a different color above
    	if (s->board[i-s->c] != s->board[i] && s->board[i-s->c] > 96)
        {
			// If so, then it finds the desired color it wants to swap with
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
				// Performs the swap
                if ((ds->Find(j) != ds->Find(i)) && (s->board[i] == s->board[j]))
				{
                    swap1 = i-s->c;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

// Checks to see if a swap with the element to the left is valid
void checkleft(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	// Making sure the element to the left exists
	if (i%s->c-1 >= 0)
    {
		// Checking to see if there's a different color to the left
    	if (s->board[i-1] != s->board[i] && s->board[i-1] > 96)
        { 
			// If so, then it finds the desired color to swap with and swaps them
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if (ds->Find(j) != ds->Find(i) && (s->board[i] == s->board[j]))
                {
                    swap1 = i-1;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

// The same concept as before, but it checks the cell to the right
void checkright(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	// Checks to see if the right is valid
	if (i%s->c+1 < s->c)
    {
		// Makes sure there's a different color to the right
    	if (s->board[i+1] != s->board[i] && s->board[i+1] > 96)
        {
			// Finds the desired swap color and performs the swap
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if ((ds->Find(j) != ds->Find(i)) && (s->board[i] == s->board[j]))
                {
                    swap1 = i+1;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

// Checks the cell below for possible swap
void checkbottom(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	// Checks to see if the cell exists
	if (i+s->c < s->board.size())
    {
		// Makes sure there's a different color below
    	if (s->board[i+s->c] != s->board[i] && s->board[i+s->c] > 96)
        {
			// Finds the desired swap color and performs the swap
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if ((ds->Find(j) != ds->Find(i)) && (s->board[i] == s->board[j]))
                {
                    swap1 = i+s->c;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

// Swaps 2 random cells if no swap has already been made (fail safe swap method)
void swaprandom(DisjointSet *&ds, Superball *&s, unsigned int &swap1, unsigned int &swap2)
{
	// The first element loops increments through the board
	for (unsigned int i = 0; i < s->board.size(); i++)
	{
		// Once it finds a color, it starts with the second element
		if (s->board[i] > 96)
		{
			// The second element decrements through the board from the back
			for (unsigned int j = s->board.size()-1; j >= 0; j--)
			{
				// Once it finds the second color, it performs the swap
				if (s->board[j] > 96 && i != j)
				{
					swap1 = i;
					swap2 = j;
					return;
				}
			}
		}
	}

}
