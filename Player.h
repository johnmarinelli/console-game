#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Globals.h"

class Player : public Entity
{
private:
	void moveRight()
	{
		if(mRect.mX < WIDTH){
			mRect.mX++;
		}
	}
	
	void moveLeft()
	{
		if(mRect.mX > 1){
			mRect.mX--;
		}
	}

	void moveUp()
	{
		if(mRect.mY > 1){
			mRect.mY--;
		}
	}

	void moveDown()
	{
		if(mRect.mY < HEIGHT){
			mRect.mY++;
		}
	}
	
public:
	char mGFX;

	Player() : mGFX('p')
	{
		setRect(1,1,1,1);
	}

	void handleInput(char input)
	{
		switch(input)
		{
		case 'l': moveLeft(); break;
                case 'r': moveRight(); break;
                case 'u': moveUp(); break;
                case 'd': moveDown(); break;
                default: break;		
		}
	}

	void paint()	
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}
} player;

#endif
