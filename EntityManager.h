#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <vector>
#include <algorithm>

class EntityManager
{
private:
	std::vector<Entity*> mEntities;
	friend class CollisionSystem;

	void remove(int index)
	{
		mEntities.erase(mEntities.begin() + index);
	}
	
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

	void update()
	{
		mEntities.erase(std::remove_if(mEntities.begin(),
									   mEntities.end(),
									   [](Entity* e){ return !(e->isActive()); }), mEntities.end());	
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
