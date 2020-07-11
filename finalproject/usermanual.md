# Dungeon Crawler User Manual
## How to Run
### Using Terminal on a UTK EECS machine
Clone this repository to the computer. Run make to compile the program and then ./main to execute the program after it compiles

## Controls
### Starting the Game
Enter *B* to start the game after the starting text comes up. After that, enter *E*, *M*, or *H* for Easy, Medium, or Hard difficulty.
The map is bigger, health is smaller, and bonus points greater for harder difficulties. Entering *D* will put you in debug mode giving you a full map and the location of the exit. 

*Be careful! On Hard, some enemies can defeat you in one fight!*
### Moving Around the Map
You can move in four directions- up, down, left, and right. Each time you enter a room, you will be prompted on which way(s) you can go.
Enter *w* to go up, *s* to go down, *a* to go left,  and *d* to go right. 
You can look at your map with *m*. This will show you what rooms you've been too and which ones are waiting to be explored.
You can examine your inventory with *i* and use an item with *u*.
### Combat
Combat starts when you enter an enemy room. You can fight with *f* or retreat with *r*. If you run away, the enemy will stay in the room.
If you fight, you take the first move. Use *n* to attack, *i* to use an item, and *r* to retreat. If you kill an enemy, you get 5000 points.

*Dying is bad. If you lose all of your health, you die and the game ends immediately!*
## Items
There are several items hidden around the dungeon. These items either increase your health or your attack strength. You can use health items in and outside of battle, but you can only use weapons in battle. If you use an item once, it is gone forever. Be careful about how you use them.

## Known Bugs
There are no known bugs.

## What do I need to play this game?
All you need to play Dungeon Crawler is a keyboard and access to a UTK EECS machine. This game can work on other machines, but it is guaranteed to work
on a EECS machine.
