#ifndef UTILITIES_H
#define UTILITIES_H

/*
* This file is for utility functions used by map-gen.cpp
* 
*/
 
#include "Room.h"
#include "CheckCollision.h"

/*
* Find the nearest neighbor to rect
*/

bool identity(const Room& a, const Room& b)
{
	return (&a == &b);
}

Room& findNearestNeighbor(Room& start, std::vector<Room>& rooms)
{
	//for some reason this function isn't working
	//...fix it
	if(start.mRect.mWidth > WIDTH){
		Room r;
		return r;
	}

	for(auto& room : rooms)
	{
		if(!identity(start, room)){
			if(checkCollision(start.mRect, room.mRect)){
				std::cout << "Found neighbor ...   \n";
				return room;
			}
		}
	}
	
	//create a 'scanner' room if there's no collision
	//Room scanner(start.mRect.mX - 1, start.mRect.mY - 1, start.mRect.mWidth + 1, start.mRect.mHeight + 1);
	
	//expand start's mRect to scan space.  start's mRect is restored in calling function
	start.mRect.mX--;
	start.mRect.mY--;
	start.mRect.mWidth++;
	start.mRect.mHeight++;

	return findNearestNeighbor(start, rooms);
}

#endif
