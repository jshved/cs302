#ifndef RANDOMMAP_H
#define RANDOMMAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Creating a random map given the size
vector<int> CreateRandomMap(int size)
{
  vector <int> rooms;
  int n = sqrt(size);
  int startpos, endpos;

  srand (time(NULL));

  // Generating the spots for the start and end room
  startpos = 0;
  endpos = rand() % (size-1) + 1;

  // Creating a square map
  rooms.resize(n*n, -1);

  // Placing the start and end room
  rooms[startpos] = 0;
  rooms[endpos] = 1;

  // Randomly placing the rest of the rooms
  for (int i = 1; i < (n*n); i++)
  {
    // If the map[i] already exists
    if (rooms[i] != -1)
      continue;

    unsigned int roomtype;
    unsigned int prob;

    // Can be rooms 2, 3, or 4
    // 2 - Boss - 20% chance
    // 3 - Empty - 50% chance
    // 4 - Points - 30% chance
    prob = rand() % 10;
  
    // 0-2 (30%) - Empty
    if (prob <= 2)
      roomtype = 3;

    // 3-4 (20%) - Item Room
    if (prob >= 3 && prob <= 4)
      roomtype = 5;

    // 5-7 (30%) - Points
    if (prob >= 5 && prob <= 7)
      roomtype = 4;

    // 8-9 (20%) - Boss
    if (prob >= 8)
      roomtype = 2;

    rooms[i] = roomtype;
  }
return rooms;
}

// Creating the debug map
vector<int> CreateDebugMap(int size)
{
  vector <int> rooms;
  rooms.resize(size);

  // Placing all rooms for testing
  for (unsigned int i = 0; i < rooms.size(); i++)
  {
    if(i == 0)
      rooms[i] = 0;
    else if(i > 0 && i < 3)
      rooms[i] = 2;
    else if(i == 3)
      rooms[i] = 3;
    else if(i > 3 && i < 6)
      rooms[i] = 4;
    else if(i > 5 && i < 8)
      rooms[i] = 5;
    else if(i == 8)
      rooms[i] = 1;
  }

  // Printing out the map for testing purposes
  for (int i = 0; i < rooms.size(); i++)
  {
	int n = sqrt(size);
    if(i % n == 0) cout << endl;
    cout << rooms[i];
  }
  cout << '\n';
  return rooms;
}

#endif

