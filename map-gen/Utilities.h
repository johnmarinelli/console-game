#ifndef UTILITIES_H
#define UTILITIES_H

/*
* This file is for utility functions used by map-gen.cpp
* 
*/
 
#include "Hallway.h"
#include "CheckCollision.h"

#include <algorithm>

int getRandomNumber(int min, int max)
{
	std::random_device rd;

    std::default_random_engine reng(rd());

	int random = 0;
	
	if(min < max){
    	std::uniform_int_distribution<int> rand(min, max);
		random = rand(reng);
	}
	
	//sometimes we'll get an instance where the max is less than the min 
	//in Map::connect
	else{
		std::uniform_int_distribution<int> rand(max, min);
		random = rand(reng);
	}
    
	return random;
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
Hallway connect(Room& a, Room& b)
{
	Rectangle aRect = a.mRect;
	Rectangle bRect = b.mRect;

	int dx = bRect.mX - (aRect.mX + aRect.mWidth);
	int dY = bRect.mY - aRect.mY;

	int minPoint = 0, maxPoint = 0;

	minPoint = std::max(aRect.mY, bRect.mY);
	maxPoint = std::min(aRect.mY + aRect.mHeight, bRect.mY + bRect.mHeight) - HALLWAY_HEIGHT;

	int yCoord = (aRect.mY == bRect.mY ? getRandomNumber(aRect.mY + HALLWAY_HEIGHT+1, aRect.mY + aRect.mHeight - HALLWAY_HEIGHT-1) : getRandomNumber(minPoint, maxPoint));

	//setting GFX relative to mGFX's (0,0) based position
	if(a.setGFX(FLOOR_CHAR, (yCoord-aRect.mY)+1, aRect.mWidth-1) == false){
		printf("connectRooms a");
	}
		
	if(b.setGFX(FLOOR_CHAR, (yCoord-bRect.mY)+1, 0) == false){
		printf("connectRooms b");
	}

	return Hallway(aRect.mX + aRect.mWidth, yCoord, dx, HALLWAY_HEIGHT);
}


#endif
