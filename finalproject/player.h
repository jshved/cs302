#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <string>
#include <math.h>
#include <stdio.h>
#include "room.h"

using namespace std;

class Player
{
  public:
    int health;
    int attack;
    int moves; //Total amount of moves made
    int points;
    int position;
    int last_room_index;
    Room* current;
    Player(char);
    int gridSize;
    void status();
    void nextMove(char m);
    void endPoints();
    void useItem();

    map<vector<int>, string> inventory;
    map<vector<int>, string>::iterator iit, eit;
    map<vector<int>, string> equip;
};


#endif
