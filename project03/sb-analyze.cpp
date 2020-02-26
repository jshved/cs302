// sb-analyze.cpp
// project03
// Author: Logan Tillman
// Date: February 26, 2020

/* This program will analyze a superball game board and print out the possible scoring set */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>
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

// This function analyzes the superball board and prints out possible scoring sets
void analyze_superball(DisjointSet *&ds, Superball *&s);

main(int argc, char **argv)
{
	Superball *s;
	DisjointSet *ds;

	// Initializing the classes
	s = new Superball(argc, argv);
	ds = new DisjointSetByRankWPC (s->r*s->c);

	// Analyzing the board
	analyze_superball(ds, s);

}

// This function analyzes the superball board and prints out possible scoring sets
void analyze_superball(DisjointSet *&ds, Superball *&s)
{
	vector <int> occurances;
	int cells;
	
	cells = s->r * s->c;
	occurances.resize(cells, 0);

	// Looping through every cell in the board
    for (int i = 0; i < cells; i++)
    {
        int top, left, right, bottom;

        top = i - s->c;
        left = i % s->c - 1;
        right = i % s->c + 1;
        bottom = i + s->c;

		// Checks to see if the top exists
        if(top >= 0)
        {
			// Checks to see if the color above is the same
            if(s->board[top] == s->board[i] && s->board[i] > 96)
            {
				// Calls union on the color
                if(ds->Find(top) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(top));
            }
        }

		// Checks to see if the bottom exists
        if(bottom < cells)
        {
			// Checks to see if the color below is the same
            if(s->board[bottom] == s->board[i] && s->board[i] > 96)
            {
				// Calls union on the colors
                if(ds->Find(bottom) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(bottom));
            }
        }

		// Checks to see if the left exists
        if(left >= 0)
        {
			// Checks to see if the color to the left is the same
            if(s->board[i-1] == s->board[i] && s->board[i] > 96)
            {
				// If so, it unions them
                if(ds->Find(i-1) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(i-1));
            }
        }

		// Checks to see if the cell to the right exists
        if(right < s->c)
        {
			// Checks to see if the colors are the same
            if(s->board[i+1] == s->board[i] && s->board[i] > 96)
            {
				// If so, it unions them
                if(ds->Find(i+1) != ds->Find(i))
                    ds->Union(ds->Find(i), ds->Find(i+1));
            }
        }
    }

	// Tracks the size of the groups
    for (int i = 0; i < cells; i++)
	{
		if (s->board[i] > 96)
			occurances[ds->Find(i)]++;
	}

    cout << "Scoring sets:\n";

	// Loops through all color groups
    for (unsigned int i = 0; i < occurances.size(); i++)
    {
		// Checks to see if the group size is high enough to be scored
        if (occurances[i] >= s->mss)
        {
			// If so, it checks to see if one of the cells falls within a goal
            for (unsigned int j = 0; j < s->goals.size(); j++)
            {
				// If it falls within a goal, it scores the group
                if (s->goals[j] == 1 && ds->Find(j) == i)
                {
                    printf("  Size:%3d  Char:%2c  Scoring Cell:%2d,%d\n", occurances[i], s->board[j], j/s->c, j%s->c);
                    break;
                }
            }
        }
    }
}
