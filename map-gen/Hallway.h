#ifndef HALLWAY_H
#define HALLWAY_H

/*
* This class is an extension of Room
* A hallway will be 'rooms' that connect rooms
*/
#include "Room.h"

const char HALLWAY_CHAR = '-';

struct Hallway : public Room
{
private:
    void destroySideWalls()
    {
		//look in Room ctor to see which order walls are constructed
		//right wall
        mWalls.erase(mWalls.begin() + 1);
		//left wall
        mWalls.erase(mWalls.begin() + 3);
    }

public:
	Hallway() : Room()
	{
	}
	
	Hallway(const Room& room) : Room(room)
	{
	}

	Hallway(int x, int y, int width, int height) : Room(x, y, width, height)
	{
		destroySideWalls();
	}
};

#endif
