#ifndef HALLWAY_H
#define HALLWAY_H

/*
* This class is an extension of Room
* A hallway will be 'rooms' that connect rooms
*/
#include "Room.h"

const char HALLWAY_CHAR = '-';
const int HALLWAY_HEIGHT = 3;

struct Hallway : public Room
{
private:
    void destroySideWalls()
    {
		//right wall
        mWalls.erase(mWalls.begin() + 1);
		//left wall
        mWalls.erase(mWalls.begin() + 3);

		//remove walls from GFX
		for(int row = 0; row < mGFXHeight; ++row){
			for(int col = 0; col < mGFXWidth; ++col){
				if((col == 0 && row > 0 && row < mGFXHeight - 1)
					|| (col == mGFXWidth - 1 && row > 0 && row < mGFXHeight - 1)){
					setGFX(FLOOR_CHAR, row, col);
				}
			}	
		}
    }

public:
	Hallway() : Room()
	{
		destroySideWalls();
	}
	
	Hallway(const Room& room) : Room(room)
	{
		destroySideWalls();
	}

	Hallway(int x, int y, int width, int height) : Room(x, y, width, height)
	{
		destroySideWalls();
	}

	Hallway(const Rectangle& rect) : Room(rect)
	{
	}

	~Hallway()
	{
	}
};

#endif
