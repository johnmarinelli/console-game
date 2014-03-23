#ifndef UTILITIES_H
#define UTILITIES_H

/*
* This file is for utility functions used by map-gen.cpp
* 
*/
 
#include "Hallway.h"
#include "CheckCollision.h"

const int HALLWAY_HEIGHT = 3;

int getRandomNumber(int min, int max)
{
	std::random_device rd;

    std::default_random_engine reng(rd());
    std::uniform_int_distribution<int> rand(min, max);
    
	return rand(reng);
}

bool identity(const Room& a, const Room& b)
{
	return (&a == &b);
}

/*
*	specialized collision checking function with scanners
*/ 
Room* checkCollision(const Rectangle& scanner, std::vector<Room>& rooms)
{
	for(auto& room : rooms)
	{
		if(checkCollision(scanner, room.mRect))
		{
			return &room;
		}
	}
	
	return NULL;
}

/*
*	Left-Right connection
*	Used in: map-gen.cpp::connectRooms()
*/
Hallway connect(const Room& a, const Room& b)
{
	Rectangle aRect = a.mRect;
	Rectangle bRect = b.mRect;

	int dx = bRect.mX - (aRect.mX + aRect.mWidth);
	int dY = bRect.mY - aRect.mY;

	return Hallway(aRect.mX + aRect.mWidth, getRandomNumber(aRect.mY + HALLWAY_HEIGHT, aRect.mY + aRect.mHeight - HALLWAY_HEIGHT), dx + 1, HALLWAY_HEIGHT);
}


#endif
