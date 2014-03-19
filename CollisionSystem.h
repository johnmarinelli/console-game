#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "EntityManager.h"
#include "Globals.h"
#include "QuadTree.h"

class CollisionSystem
{
private:
	QuadTree mQuadTree;
	const std::vector<Entity*>& mEntities;

	bool checkCollision(const Entity& a, const Entity& b)
	{
	    int aLeft = a.mRect.mX;
	    int aTop = a.mRect.mY;
	    int aRight = aLeft + a.mRect.mWidth;
	    int aBottom = aTop + a.mRect.mHeight;

	    int bLeft = b.mRect.mX;
	    int bTop = b.mRect.mY;
	    int bRight = bLeft + b.mRect.mWidth;
	    int bBottom = bTop + b.mRect.mHeight;

	    if (aLeft >= bRight) return false;
	    if (aRight <= bLeft) return false;
	    if (aBottom <= bTop) return false;
	    if (aTop >= bBottom) return false;

    	return true;
	}

	void updateQuadTree()
	{
		mQuadTree.clear();

		for(auto i : mEntities){
			mQuadTree.insert(i);
		}
	}

	void collision(int& coll)
	{
		std::vector<Entity*> v;

 	      	for(int i = 0; i < mEntities.size(); i++){
        	        v.clear();
        	        mQuadTree.getObjects(v, mEntities[i]->mRect);
	
	                for(int j = 0; j < v.size(); j++){
        	                if(v[j] != mEntities[i]){
        	                        if(checkCollision(*mEntities[i], *v[j])){
										(*mEntities[i]).handleCollision(*v[j]);
										coll++;
        	                        }
        	                }
        	        }
        	}
	}

public:

	CollisionSystem(const EntityManager& em) : mQuadTree(0, Rectangle(0, 0, WIDTH, HEIGHT)), mEntities(em.mEntities)
	{
	}

	void update(int& coll)
	{
		updateQuadTree();
		collision(coll);
	}	

};

#endif
