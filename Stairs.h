#ifndef STAIRS_H
#define STAIRS_H

#include "Entity.h"

struct Stairs : public Entity
{
	char mGFX;
	bool mDown;
	
	Stairs() : mDown(false), mGFX('v')
	{
	}

	Stairs(Rectangle rect) : mDown(false),  mGFX('v')
	{
		setRect(rect);
	}

	void handleCollision(Entity& e)
	{
		if(e.mType == PLAYER){
			mDown = true;
		}	
	}

	void paint()
	{
	    moveTo(mRect.mX, mRect.mY);
        printf("%c", mGFX);
	}

	bool isActive()
	{
		return true;	
	} 
};

#endif
