#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <vector>

class EntityManager
{
private:
	std::vector<Entity*> mEntities;
	
public:
	EntityManager() 
	{
	}

	const int size()
	{
		return mEntities.size();
	}

	void add(Entity* e)
	{
		mEntities.push_back(e);
	}

	void paint()
	{
		for(auto i : mEntities){
			i->paint();
		}
	}

	Entity* operator[](int index)
	{
		if(index > -1 && index <= mEntities.size() - 1)
			return mEntities[index];
		else
			return nullptr;
	}
};

#endif
