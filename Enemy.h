#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Globals.h"
#include "Statistics.h"

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
		setType(ENEMY);
		setRect(rect);
	}

	void handleCollision(const Entity& e)
	{
	}
	
	void paint()
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}

	void attack(const Entity& e)
	{	
	}
};

#endif
