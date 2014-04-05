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
	
		for(auto i : mEntities){
			i->update();
		}
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
	
	/*
	*  All elements of mEntities are made on the stack, so we don't delete
	*/
	void reset()
	{
		mEntities.erase(std::remove_if(mEntities.begin(), 
									mEntities.end(), 
									[](Entity* e){ return true; }), mEntities.end());
	}
};

#endif
