// solution.cpp
// Challenge 09: sequence alignment
// Author: Logan Tillman
// Date: April 16, 2020

/* This program will compute each value in the matrix for the sequence alignment using
   dynamic programming.*/

#include <iostream>
#include <vector>
using namespace std;

// Function used for scoring the diagonal
int Score(const int &i, const int &j, const string &seq1, const string &seq2);

// Function used to determine the max between three numbers
int Max(const int &num1, const int &num2, const int &num3);

int main(int argc, char *argv[]) 
{
	vector<vector<int>> matrix;
	string seq1, seq2;
	int gappenalty = -1;
	
	// Reading in the sequences
	cin >> seq1 >> seq2;

	// Creating the matrix
	matrix.resize(seq1.size()+1);
	for (unsigned int i = 0; i < matrix.size(); i++)
		matrix[i].resize(seq2.size()+1);

	// Setting up the initial gaps
	for (unsigned int i = 1; i < matrix.size(); i++)
		matrix[i][0] = matrix[i-1][0] - 1;
	for (unsigned int j = 1; j < matrix[0].size(); j++)
		matrix[0][j] = matrix[0][j-1] - 1;

	// Scoring the matrix
	for (unsigned int i = 1; i < matrix.size(); i++)
	{
		for (unsigned int j = 1; j < matrix[i].size(); j++)
		{
			int diag = matrix[i-1][j-1];
			int left = matrix[i][j-1];
			int top = matrix[i-1][j];

			// Comparing the scores between the possible moves and assigning the maximum
			matrix[i][j] = Max(diag + Score(i, j, seq1, seq2), left + gappenalty, top + gappenalty); 
		}
	}

	// Printing out the end result
	cout << matrix[matrix.size()-1][matrix[0].size()-1] << '\n';

    return 0;
}

// Function used to score the diagonal
int Score(const int &i, const int &j, const string &seq1, const string &seq2)
{
	// If the characters in the sequences match
	if (seq1[i-1] == seq2[j-1])
		return 1;

	// If they're mismatched
	else
		return -1;
}

// Function that returns the maximum between three integers
int Max(const int &num1, const int &num2, const int &num3)
{
	if (num1 >= num2)
	{
		if (num1 >= num3)
			return num1;
		else
			return num3;
	}
	else if (num2 >= num3)
		return num2;
	else
		return num3;
}
