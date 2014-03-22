#ifndef UTILITIES_H
#define UTILITIES_H

/*
* This file is for utility functions used by map-gen.cpp
* 
*/
 
#include "Room.h"
#include "CheckCollision.h"
#include <math>

/*
* Find the nearest neighbor to rect
*/

bool identity(const Room& a, const Room& b)
{
	return (&a == &b);
}

Room& findNearestNeighbor(Room& start, std::vector<Room>& rooms)
{
	//go left to right
	//find distance to next element
	
}

#endif
