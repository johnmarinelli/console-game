#ifndef LEVELHALL_H
#define LEVELHALL_H

#include "map-gen/Hallway.h"

#include "Entity.h"
#include <vector>

class LevelHallway : Hallway
{
private:
    std::vector<Entity*> mEntities;

public:
    LevelHallway()
    {
    }

	LevelHallway(const Rectangle& rect) : Hallway(rect)
	{
	}
};

#endif                                   
