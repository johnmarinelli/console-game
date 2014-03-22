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
	Hallway() : Room()
	{
	}
	
	Hallway(const Room& room) : Room(room)
	{
	}

	Hallway(int x, int y, int width, int height) : Room(x, y, width, height)
	{
	}

	void draw()
	{
		std::cout << MOVE_TO_0_0;

		drawRect(mRect, HALLWAY_CHAR);
	}
};

#endif
