// Challenge 06: Palindrome Permutation
// Author: Logan Tillman
// Date: February 6 2020

/*	This is a program that will take a string and determine 
 	if any combination of the word is a palindrome */

#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <string>

using namespace std;

bool is_palindrome(const string &s);

int main(int argc, char *argv[]) {
	string unparsedword, word;

	// Reads in each string
	while (getline(cin, unparsedword))
	{
		// Initializing/Clearing the parsed word string
		word = "";

		// Checking the ASCII values for the strings to remove all symbols and spaces
		for (unsigned int i = 0; i < unparsedword.size(); i++)
		{
			if ((unparsedword[i] > 64 && unparsedword[i] < 91) ||
				(unparsedword[i] > 96 && unparsedword[i] < 123))
				word += unparsedword[i];
		}

		// Calling the is_palindrome function to determine if the string is a palindrome
		if (is_palindrome(word) == false)
			printf("\"%s\" is not a palindrome permutation\n", unparsedword.c_str());
		else
			printf("\"%s\" is a palindrome permutation\n", unparsedword.c_str());

		// Emptying the unparsedword string
		unparsedword = "";
	}	

  return (0);
}

// This function determines if a string is a palindrome or not
bool is_palindrome(const string &s)
{
    unordered_map <char, int> umap;
    unordered_map <char, int>::const_iterator uit;
	int numodd;
	
	numodd = 0;

	for (unsigned int i = 0; i < s.size(); i++)
    {
		// If a character in the word doesn't exist in the map, I insert it
        if (umap.find(s[i]) == umap.end())
            umap.insert(make_pair(s[i], 1));

		/* If the character already exists, I increase the integer 
		   containing how many times the letter appears	*/
        else
            umap.find(s[i])->second++;
    }

    for (uit = umap.begin(); uit != umap.end(); uit++)
    {
		// Checking to see how many letters appear an odd number of times in the string
        if ((uit->second % 2) != 0)
            numodd++;
    }

	// If there's more than 1 character that appears an odd amount of times, it's not a palindrome
	if (numodd > 1)
		return false;

	// Otherwise, the word is a palindrome
	else
		return true;

}

