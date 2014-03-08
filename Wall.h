#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity
{
private:
public:
	char mGFX;

	Wall() : mGFX('w')
	{
		setRect(1,1,1,1);
		mType = WALL;
	}

	Wall(int x, int y) : mGFX('w')
	{		
		setRect(x, y, 1, 1);
	}

	void paint()
	{
        moveTo(mRect.mX, mRect.mY);
        printf("%c", mGFX);
	}
};

#endif
