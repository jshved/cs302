//Final Project 
//Making a dungeon crawler
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <string>
#include <math.h>
#include <stdio.h>
#include "randommap.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

using namespace std;

// Main
int main() {

  srand (time(NULL));
  Items it;

  char input;
  char difficulty;
  char m = 'P';
  vector <Room> grid;
  vector<int> roomTypes;
  
  //startup options and game tutorial
 cout << "You wake up dazed on a cold, barren stone floor. Your back aches from the uneven bumps and cracks that you were once laying on. Observing your surroundings, you notice you’re in another generic dungeon crawler game.\nHow typical!\nAs these games tend to go you must find a way out of the walls that confine you by any means necessary. Minimizing moves and maximizing health will ensure you get the highest score possible! The dungeon you inhabit features a bounty of traps, enemies, and puzzles. You can move in any of the cardinal directions as long as there is a room there.\nYou can show your current inventory with I and if there is an item to interact with using the command U to use an item in your inventory. Using P will allow you see you current health and points. Finally you can show the map of the dungeon with M.\n\nEnter ‘B’ to begin and best of luck to you traveller!" << endl;
  cin >> input;
  //If the user does not enter B then it will 
  //keep asking until the user enters a B
  while(input != 'B'){
    cout << "PLEASE ENTER B TO BEGIN:\n";
    cin >> input;
  }
  //There are three difficulties, easy, medium, hard
  //and fourth debug mode
  cout << "CHOOSE A DIFFICULTY:" << endl << "(E)asy  (M)edium  (H)ard  (D)ebug" << endl;
  cin >> difficulty;

  while(difficulty != 'E' && difficulty != 'M' && difficulty != 'H' && difficulty != 'D'){
    cout << "PLEASE ENTER E, M, H, or D: ";
    cin >> difficulty;
  }
  //Based on the difficulty, it will size the dungeon 
  //accordingly
  if(difficulty == 'D')
  {
    grid.resize(9);
    roomTypes = CreateDebugMap(grid.size());
  }
  else
  {
    if(difficulty == 'E')
      grid.resize(16);
    if(difficulty == 'M')
      grid.resize(25);
    if(difficulty == 'H')
      grid.resize(49);
    //This randomizes all of the room types for the 
    //dungeon
    roomTypes = CreateRandomMap(grid.size());
  }
  //These are all of the different rooms that can be spawned
  for(int i = 0; i < grid.size(); i++){
    grid[i].roomNum = i;
    grid[i].type = roomTypes[i];
    if (roomTypes[i] == 0)
      grid[i].typestring = "Start";
    if (roomTypes[i] == 1)
      grid[i].typestring = "End";
    if (roomTypes[i] == 2)
      grid[i].typestring = "Boss";
    if (roomTypes[i] == 3)
      grid[i].typestring = "Empty";
    if (roomTypes[i] == 4)
      grid[i].typestring = "Treasure";
    if (roomTypes[i] == 5)
      grid[i].typestring = "Item";
  }

  cout << '\n'; 
  Player p(difficulty);
  cout << "PLAYING ON " << difficulty << "\n";
  p.gridSize = grid.size();
  int x = sqrt(grid.size());

  int exit_room;
  for(int i = 0; i < grid.size(); i++)
  {
    //Once the exit room is reached the player can choose to continue playing for more points or to end the game
      if(grid[i].type == 1)
      {
        exit_room = i;
        break;
      }
  }
	p.position = 0;
  while(true){
    cout << "\nYou are in Room Number: " << p.position << endl;
    //This marks all of the visited rooms so you know where you have been
    if(grid[p.position].visited == true)
      cout << "You've been here before" << endl;

    if(grid[p.position].type == 1){

      int point_rooms_left = 0;
      char cont = 'x';
      bool exit;
      
      //Get number of treasure rooms
      for(int i = 0; i < grid.size(); i++)
      {
        if(grid[i].type == 4 && grid[i].visited == false) point_rooms_left++;
      }

       cout << endl << "CONGRATULATIONS! YOU FOUND THE WAY OUT!" << endl;
       cout << "You can chose to leave now or keep exploring." << endl;
       cout << "Treasure rooms left: " << point_rooms_left << endl;
       cout << "Continue exploring? (y/n)" << endl;

       cin >> cont; 

       //Check input and exit or continue
       while(true)
       {
         if(cont == 'y') 
         {
           cout << "GOOD LUCK!" << endl;
           exit = false;
           break;
         }

         if(cont == 'n')
        {
          exit = true;
          break;
        }

        cin >> cont;
       }

       if(exit) break;

    grid[p.position].visited = true;
    }
    else if(grid[p.position].type == 2 && grid[p.position].defeated != true){
      //boss or enemy text
      //interaction option
      Enemy boss;

      grid[p.position].visited = true;

      boss.EncounterEnemy();
      boss.fight(p);
      
      
      grid[p.position].defeated = true;
    }
    else if(grid[p.position].type == 3){
      cout << "There's nothing interesting in this room..." << endl;
      grid[p.position].visited = true;
    }
    else if(grid[p.position].type == 4 && grid[p.position].visited == false){

      //Calculate the number of points you get and add them to the player's total
      int value;
      srand (time(NULL));
      value = rand() % 2000 + 2000;
      p.points += value;
     
      cout << "You found a treasure room!" << endl;
      cout << "It's worth " << value << " points!!" << endl;

      grid[p.position].visited = true;
    }
    else if(grid[p.position].type == 5 && grid[p.position].visited == false){
      //item room

	  //random number based on size of item map
      int RNG = rand() % it.item.size();

      it.mit = it.item.begin();

	  //go to random element of the map
      advance(it.mit, RNG);

      cout << "You have recieved a " << it.mit->second << endl;

	  //add that item to inventory
      p.inventory.insert(pair<vector<int>, string>(it.mit->first, it.mit->second));

      grid[p.position].visited = true;
    }

   if(p.health <= 0)
   {
     cout << "YOU DIED..." << endl;
     p.points = 0;
     break;
   }
  
   if(p.position == 0)
   grid[0].visited = true;

   cout << "You can move: ";
   if(p.position - sqrt(grid.size()) > 0){
     cout << " up (w) ";
   }
   if(p.position + sqrt(grid.size()) < grid.size()){
     cout << " down (s) ";
   }
   if(p.position % x != 0){
     cout << " left (a) ";
   }
   if(p.position % x != (x-1)){
     cout << " right (d) ";
   }
   cout << ":\n";
  
   cin >> m;
   if(m == 'q'){
     break;
   }
   if(m == 'm'){

  cout << "\n\n";

  for(int i = 0; i < grid.size(); i++){

    if(grid[i].visited == true)
      cout << grid[i].type << " ";
    else
      cout << "- ";

    if((i+1)%x == 0)
    cout << endl;

  }
  cout << "\n\n";
  }
   p.nextMove(m);

   cout << "__________________________" << endl << endl;
  }
  
    
 p.endPoints();  
}


