#ifndef ENTITY_H
#define ENTITY_H

#include "Rectangle.h"
#include "Statistics.h"

enum EntityType 
{
	NONE,
	PLAYER,
	WALL,
	ENEMY,
};

enum MessageType
{
	MESSAGETYPE_NONE,
	MESSAGETYPE_ATTACK,
};

class Entity
{
private:
public:
	char mGFX;

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

	virtual void handleCollision(Entity& e)
	{
	}

	/*
	* params: type, entity
	* messagetypes: 
	*/
	virtual void receiveMessage(MessageType type, Entity& e)
	{
	}

	/*
	* params: type, statistics
	* messagetypes: ATTACK,
	*/
	virtual void receiveMessage(MessageType type, Statistics stats)
	{	
	}

	virtual bool isActive()
	{
		return false;
	}
};

#endif
