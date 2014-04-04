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
	HEALTHPACK,
};

enum MessageType
{
	MESSAGETYPE_NONE,
	MESSAGETYPE_ATTACK,
	MESSAGETYPE_GETHEALTH,
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

	void setRect(Rectangle rect)
	{
		mRect = rect;
	}

	virtual void handleCollision(Entity& e)
	{
	}

	/*
	* params: type, entity
	* messagetypes: GETHEALTH,
	*/
	virtual void receiveMessage(MessageType type, Entity& sender)
	{
	}

	/*
	* params: type, statistics
	* messagetypes: ATTACK,
	*/
	virtual void receiveMessage(MessageType type, const Statistics& stats)
	{	
	}

	virtual void update()
	{	
	}
	
	virtual void moveBack()
	{
	}

	virtual bool isActive()
	{
		return false;
	}

	virtual const Statistics& getStatistics()
	{
	}
};

#endif
