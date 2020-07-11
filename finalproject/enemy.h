#ifndef ENEMY_H
#define ENEMY_H
using namespace std;

class Enemy{

  public:
    Enemy();
    void EncounterEnemy();
    void PrintHealth();
    void PrintName();
    void PrintAttackStyle();
    void PrintMaxHit();
    void fight(Player&);

  private:
    string name;
    int health;
    string attackstyle;
    int maxhit;

};

Enemy::Enemy()
{
  srand (time(NULL));

  // 1 = Melee, 2 = Ranged, 3 = Magic
  int randomnum = rand() % 3 + 1;

  name = "Boss Name";

  // Setting the boss stats
  if (randomnum == 1)
  {
	name = "Dr. Emrich";
    attackstyle = "Melee";
	maxhit = 10;
  }
  else if (randomnum == 2)
  {
	name = "Dr. Marz";
    attackstyle = "Ranged";
	maxhit = 20;
  }
  else if (randomnum == 3)
  {
	name = "Dr. Plank";
	attackstyle = "Magic";
	maxhit = 30;
  }

  // Setting the boss health value
  health = 100;
}

// Printing information when encountering boss
void Enemy::EncounterEnemy()
{
  PrintName();
  PrintHealth();
  PrintAttackStyle();
  PrintMaxHit();
}

// Prints the remaining health of the boss
void Enemy::PrintHealth()
{
  if(health < 0)
  health = 0;
  
  cout << "Remaining Health: " << health << '\n';
}

// Prints the name of the boss
void Enemy::PrintName()
{
  cout << "You have encountered " << name << "!\n";
}

// Prints which attack style the boss uses
void Enemy::PrintAttackStyle()
{
  cout << "Attack Style: " << attackstyle << '\n'; 
}

// Prints the max hit of the boss
void Enemy::PrintMaxHit()
{
  cout << "Max Hit: " << maxhit << '\n';
}

// Initiates the fight between the boss and the player
void Enemy::fight(Player &p)
{
  char answer;

  // Player chooses whether to fight or retreat
  cout << "A monster huddles in the corner. It hears you enter the room/nand charges at you.";
  cout << endl << "What do you do?" << endl;
  cout << "Fight it! (f) OR Be a coward and close the door. (r)" << endl;
  
  cin >> answer;

  while(answer != 'f' && answer != 'r')
  {
    cout << "Enter 'f' to fight the monster or 'r' to run away." << endl;
    cin >> answer;
  }

  // If the player retreats
  if(answer == 'r')
  {
    // Returns the player to the previous room
    p.position = p.last_room_index;
    cout << endl << "You quickly shut the door with cowardice, but you have only wasted time." 
		 << endl << endl;
    cout << "You are still in Room " << p.position << ". Your movement options are the same." << endl;
    return;  
  }

  // If the player fights
  if(answer == 'f')
  {
    cout << "You courageously start a face the monster!" << endl << "GOOD LUCK!" << endl;

  bool retreat = false;
  
  while(health > 0 && p.health > 0)
  {
      char move;
      
	  do {
      // Player's options during the fight
      cout << '\n' << "You move! Your options are: " << endl;
      cout << "Attack!!! (n)" << endl;
      cout << "Use a item! (i)" << endl;
      cout << "Make a 'tactical' retreat! (r)" << endl;
      cin >> move;
	  } while (move != 'n' && move != 'i' && move != 'r');

      switch(move)
       {
          // Executes when the player attacks
          case('n'):
            if(p.equip.empty())
              cout << "\nYou attack with your fists!" << endl;
            else{
              p.eit = p.equip.begin();
              cout << "\nYou attack with a " << p.eit->second << endl;
            }

            cout << "You deal " << p.attack << " damage!" << endl;
            health -= p.attack;
            break;

          // The player opens up the inventory
          case('i'):
              p.useItem();
              continue;
              break;
          
          // The player retreats
          case('r'):
            cout << endl << "You retreat! Were you scared or almost dead? Who knows?" << endl;
            retreat = true;
            p.position = p.last_room_index;
            break;
       }
      if(retreat) break;
      
      cout << "The monster attacks!" << endl;

      // The monster deals a random amount of damage to the player
      int damage = maxhit - rand() % 5;
      p.health -= damage;
      cout << "You took " << damage << " damage! Ouch!!!" << endl;

      if(p.health <= 0){
        p.health = 0;
		p.points = 0;
	  }
        
      // Printing the player and boss health after each turn
      cout << "Your health: " << p.health << endl;
      PrintHealth();
      cout << "__________________________" << endl << endl;
       
  }
  if(retreat) return;

  // If you kill the boss, you gain 5000 points
  if(health <= 0){
  cout << "The monster vanishes in a puff of smoke. You have won!" << endl;
  cout << "GAIN 5000 POINTS" << endl;
  p.points += 5000;
  }

  }

}

#endif
