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

main(int argc, char **argv)
{
	Superball *s;
	DisjointSet *ds;
	vector <int> occurances;
	int cells;

	s = new Superball(argc, argv);
	ds = new DisjointSetByRankWPC (s->r*s->c);
	cells = s->r * s->c;
	occurances.resize(cells, 0);

	for (int i = 0; i < cells; i++)
	{
		int top, left, right, bottom;
	
		top = i - s->c;
		left = i % s->c - 1;
		right = i % s->c + 1;
		bottom = i + s->c;

		if(top >= 0)
		{
			if(s->board[top] == s->board[i] && s->board[i] > 96)
			{
				if(ds->Find(top) != ds->Find(i))
					ds->Union(ds->Find(i), ds->Find(top));
			}
		}

		if(bottom < cells)
		{
			if(s->board[bottom] == s->board[i] && s->board[i] > 96)
			{
				if(ds->Find(bottom) != ds->Find(i))
					ds->Union(ds->Find(i), ds->Find(bottom));
			}
		}

		if(left >= 0)
		{
			if(s->board[i-1] == s->board[i] && s->board[i] > 96)
			{
				if(ds->Find(i-1) != ds->Find(i))
					ds->Union(ds->Find(i), ds->Find(i-1));
			}
		}

		if(right < s->c)
		{
			if(s->board[i+1] == s->board[i] && s->board[i] > 96)
			{	
				if(ds->Find(i+1) != ds->Find(i))
					ds->Union(ds->Find(i), ds->Find(i+1));
			}
		}
	}

	for (int i = 0; i < cells; i++)
		occurances[ds->Find(i)]++;

	cout << "Scoring sets:\n";

	for (unsigned int i = 0; i < occurances.size(); i++)
	{
		if (occurances[i] >= s->mss)
		{
			for (unsigned int j = 0; j < s->goals.size(); j++)
			{
				if (s->goals[j] == 1 && ds->Find(j) == i)
				{
					printf("  Size:%3d  Char:%2c  Scoring Cell:%2d,%d\n", occurances[i], s->board[j], j/s->c, j%s->c);
					break;
				}
			}
		}
	}
}
