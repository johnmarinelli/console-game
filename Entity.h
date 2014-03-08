#ifndef ENTITY_H
#define ENTITY_H

#include "Rectangle.h"

enum EntityType 
{
	NONE,
	PLAYER,
	WALL,
};

class Entity
{
private:
public:
	EntityType mType;
	Rectangle mRect;
	Entity() : mType(NONE), mRect() {};

	virtual void paint() = 0;

	void setType(EntityType type)
	{
		mType = type;
	}

	void setRect(const int x, const int y, const int width, const int height)
	{
		mRect.mX = x;
		mRect.mY = y;	
		mRect.mWidth = width;	
		mRect.mHeight = height;
	}

	virtual void handleCollision(const Entity& e)
	{
	}
};

#endif
