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

void analyze_superball(DisjointSet *&ds, Superball *&s, map <int, int> &possiblescores, vector <int> &occurances);
void checktop(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);
void checkleft(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);
void checkright(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);
void checkbottom(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2);
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

	analyze_superball(ds, s, possiblescores, occurances);

	if (possiblescores.empty() == false)
	{
		maxpoints = possiblescores.begin()->second;
		location = possiblescores.begin()->first;

		for (pit = possiblescores.begin(); pit != possiblescores.end(); pit++)
		{
			if (pit->second > maxpoints)
			{
				maxpoints = pit->second;
				location = pit->first;
			}
		}

		cout << "SCORE " << location/s->c << " " << location%s->c << '\n';
	}
	else
	{
		unsigned int swap1, swap2;
		maxlength = occurances[0];
		location = 0;
		swap1 = 0;
		swap2 = 1;

		for (unsigned int i = 0; i < occurances.size(); i++)
		{
			if (occurances[i] > maxlength)
			{
				maxlength = occurances[i];
				location = i;
			}
		}

		for (unsigned int i = 0; i < s->board.size(); i++)
		{
			if (ds->Find(i) == location)
				vertices.push_back(i);
		}

		for (int i = 0; i < (int) vertices.size(); i++)
		{
			// If on left side of graph
			if (((vertices[i] % s->c) / (s->c / 2)) == 0)
			{
				if (swap1 == 0 && swap2 == 1)
					checkleft(ds, s, vertices[i], swap1, swap2);
			}

			// If on right side of graph
			else
			{
				if (swap1 == 0 && swap2 == 1)
					checkright(ds, s, vertices[i], swap1, swap2);
			}

			if (swap1 == 0 && swap2 == 1)
				checktop(ds, s, vertices[i], swap1, swap2);

			//FIXME if there are no paths, it's choosing an invalid path for it's vertices
//			cout << "vertices[i] = " << i << " " << vertices[i] << '\n';
			if (swap1 == 0 && swap2 == 1)
				checkbottom(ds, s, vertices[i], swap1, swap2);
		}

		if (swap1 == 0 && swap2 == 1)
			swaprandom(ds, s, swap1, swap2);

		cout << "SWAP " << swap1/s->c << " " << swap1%s->c << " " << swap2/s->c << " " << swap2%s->c << '\n';
	}

}

void analyze_superball(DisjointSet *&ds, Superball *&s, map <int, int> &possiblescores, vector <int> &occurances)
{
    int cells;

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
	{
		if (s->board[i] > 96)
			occurances[ds->Find(i)]++;
	}

    for (unsigned int i = 0; i < occurances.size(); i++)
    {
        if (occurances[i] >= s->mss)
        {
            for (unsigned int j = 0; j < s->goals.size(); j++)
            {
                if (s->goals[j] == 1 && ds->Find(j) == i)
                {
                    possiblescores[j] = occurances[i];
                    break;
                }
            }
        }
    }
}

void checktop(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	if (i-s->c >= 0)
    {
    	if (s->board[i-s->c] != s->board[i] && s->board[i-s->c] > 96)
        {
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if ((ds->Find(j) != ds->Find(i)) && (s->board[i] == s->board[j]))
				{
//					cout << "Updating swap in top\n";
                    swap1 = i-s->c;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

void checkleft(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	if (i%s->c-1 >= 0)
    {
    	if (s->board[i-1] != s->board[i] && s->board[i-1] > 96)
        { 
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if (ds->Find(j) != ds->Find(i) && (s->board[i] == s->board[j]))
                {
//					cout << "Updating swap in left\n";
                    swap1 = i-1;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

void checkright(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	if (i%s->c+1 < s->c)
    {
    	if (s->board[i+1] != s->board[i] && s->board[i+1] > 96)
        {
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if ((ds->Find(j) != ds->Find(i)) && (s->board[i] == s->board[j]))
                {
//					cout << "Updating swap in right\n";
                    swap1 = i+1;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

void checkbottom(DisjointSet *&ds, Superball *&s, int &i, unsigned int &swap1, unsigned int &swap2)
{
	if (i+s->c < s->board.size())
    {
		//FIXME
//		cout << i << " bottom exists\n";
    	if (s->board[i+s->c] != s->board[i] && s->board[i+s->c] > 96)
        {
            for (unsigned int j = 0; j < s->board.size(); j++)
            {
                if ((ds->Find(j) != ds->Find(i)) && (s->board[i] == s->board[j]))
                {
//					cout << "Updating swap in bottom\n";
                    swap1 = i+s->c;
                    swap2 = j;
					return;
                }
            }
        }
	}
}

void swaprandom(DisjointSet *&ds, Superball *&s, unsigned int &swap1, unsigned int &swap2)
{
	for (unsigned int i = 0; i < s->board.size(); i++)
	{
		if (s->board[i] > 96)
		{
			for (unsigned int j = s->board.size()-1; j >= 0; j--)
			{
				if (s->board[j] > 96 && i != j)
				{
//					cout << "Updating swap in random\n";
					swap1 = i;
					swap2 = j;
					return;
				}
			}
		}
	}

}
