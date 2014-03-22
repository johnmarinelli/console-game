#ifndef UTILITIES_H
#define UTILITIES_H

/*
* This file is for utility functions used by map-gen.cpp
* 
*/
 
#include "../Rectangle.h"

Rectangle& findNearestNeighbor(const Rectangle& rect, const std::vector<Rectangle>& rooms)
{
	for(auto& room : rooms)
	{
		if(&rect != &room)
		{
		}
	}
}

#endif
