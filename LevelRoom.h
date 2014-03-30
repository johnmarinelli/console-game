#ifndef LEVELROOM_H
#define LEVELROOM_H

#include "map-gen/Room.h"

#include "Entity.h"
#include <vector>

class LevelRoom : Room
{
private:
	std::vector<Entity*> mEntities;

public:
	LevelRoom()
	{
	}
	
	LevelRoom(const Rectangle& rect) : Room(rect)
	{
	}
};

#endif
