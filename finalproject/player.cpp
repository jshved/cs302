#include "player.h"

Player::Player(char difficulty)
{
  //change health and points based of difficulty
  if(difficulty == 'E' || difficulty == 'D')
  {
    health = 400;
    points = 0;
  }

  else if (difficulty == 'M')
  {
    health = 200;
    points = 1000;
  }

  else if (difficulty == 'H')
  {
    health = 100;
    points = 2000;
  }

  moves = 1;
  //set default attack
  attack = 20;

}
void Player::status()
{
  cout << "\nHEALTH: " << health << '\n';
  cout << "POINTS: " << points << '\n';
  cout << "MOVES: " << moves << '\n';
}

void Player::nextMove(char m){

  if(m == 'p'){
    status();
  }
  if(m == 'i' && inventory.size() > 0){
	  cout << '\n' << "Your Inventory:" << '\n';
    for(iit = inventory.begin(); iit != inventory.end(); iit++){
      cout << iit->second << " " << endl;
    }
  }

if(m == 'u' && inventory.size() > 0){

	useItem();

}

  last_room_index = position; //Keep track of what the last room is for combat
  int x = sqrt(gridSize);
  if(m == 'w' && position > x-1){
    cout << "You have moved up!" << endl;
    position = position - x;
    moves++;
  }
  if(m == 's' && position < gridSize - x){
    cout << "You have moved down!" << endl;
    position = position + x;
    moves++;
  }
  if(m == 'a' && position%x != 0){
    cout << "You have moved the left!"<< endl;
    position = position - 1;
    moves++;
  }
  if(m == 'd' && (position+1)% x != 0){
    cout << "You have moved to the right" << endl;
    position = position + 1;
    moves++;
  }
}

void Player::endPoints()
{
  int end;
  
  end = (health * 1.33 + points);

  cout << "Total Points Earned: " << end << '\n';

}

void Player::useItem()
{
  int itemChoice;
  bool used = false;
  int i = 0;
  //Error check in fight

  if(inventory.empty()){

    cout << '\n' << "You have no items to use.... Tough luck" << endl;

  }
  else{

  
  cout << '\n' << "Which item would you like to use?" << endl;
  //Print All Items
  for(iit = inventory.begin(); iit != inventory.end(); iit++){
      cout << "Item " << i << ": " << iit->second << '\n';
      i++;
  }    
    while(cin >> itemChoice){
      i = 0;
      for(iit = inventory.begin(); iit != inventory.end(); iit++){
        
      
		//Healing
        if(i == itemChoice && iit->first[0] == 1){

          cout << '\n' << "You have used " << iit->second << endl;
          cout << "You have gained " << iit->first[1] << " health!!" << endl;
         
          health += iit->first[1];

          cout << "Your new health total is: " << health << endl << endl;
          used = true;
        } 
		//Equipping a Weapon
        if(i == itemChoice && iit->first[0] == 0){

          eit = equip.begin();
          
          cout << endl << "You have equipped " << iit->second << endl;
          cout << "This item has " << iit->first[1] << " damage!!" << endl;

          if(attack != 20)
          attack = 20;

          attack += iit->first[1];

          cout << "Your new attack stat is: " << attack << endl;

		  //Weapons can be used multiple times, we need to use a temp map to hold the current weapon being used while deleting it from the inventory map
		  //until we equip another item
          if(equip.empty())
              equip.insert(pair<vector<int>, string>(iit->first, iit->second));
          else{

              inventory.insert(pair<vector<int>, string>(eit->first, eit->second));
              equip.insert(pair<vector<int>, string>(iit->first, iit->second));
              equip.erase(eit);
          }

          used = true;
        } 

	  //if number chosen was not a valid number
      if(used == false && i == itemChoice){
        cout << itemChoice << " is not a valid item index" << endl;
       }

	  //Removes a used item
      if(used){
        inventory.erase(iit);
        used = false;
      }

        i++;
      }
      

    break;

    }

  }
}        

