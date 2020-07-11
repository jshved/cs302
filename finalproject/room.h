#ifndef ROOM_H
#define ROOM_H

using namespace std;

class Room
{
    public:
        bool defeated;			// Stores if the boss has been defeated
        bool visited;			// Stores if the player has visited the room
        string text;			
        vector< Room * > adj;	// Storing the adjacent rooms
        string typestring;		// The room type converted to a string for output
        int type;				// The room type (integer)
        int roomNum;			// Storing which number the room is in the graph
};

#endif
