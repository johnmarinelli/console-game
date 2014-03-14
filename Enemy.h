#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Globals.h"

class Enemy : public Entity
{
private:
	Statistics mStatistics;

public:
	char mGFX;

	Enemy() : mGFX('a')
	{
		setType(ENEMY);
		setRect(2,2,2,2);
	}

	Enemy(Rectangle rect, char level) : mGFX(level)
	{
		setRect(rect.mX, rect.mY, rect.mWidth, rect.mHeight);
		setType(ENEMY);
	}

	void handleCollision(Entity& e)
	{
	}
	
	void paint()
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}

	void attack(Entity& e)
	{	
	}

	void receiveMessage(MessageType type, Statistics stats)
	{
		switch(type)
        {
            case MESSAGETYPE_ATTACK: mStatistics.Health -= stats.Damage;
                break;
            default: break;
        }
	}

	bool isActive()
	{
		return (mStatistics.Health > 0);
	}
};

#endif
