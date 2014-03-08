#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Globals.h"

class Player : public Entity
{
private:

	enum LastMove{ NONE, UP, DOWN, LEFT, RIGHT } mLastMove;

	void moveBack()
	{
		switch(mLastMove){
			case UP: mRect.mY++;
			case DOWN: mRect.mY--;
			case LEFT: mRect.mX++;
			case RIGHT: mRect.mX--;
		}	
	}

	void moveRight()
	{
		if(mRect.mX < WIDTH){
			mRect.mX++;
			mLastMove = RIGHT;
		}
	}
	
	void moveLeft()
	{
		if(mRect.mX > 1){
			mRect.mX--;
			mLastMove = LEFT;
		}
	}

	void moveUp()
	{
		if(mRect.mY > 1){
			mRect.mY--;
			mLastMove = UP;
		}
	}

	void moveDown()
	{
		if(mRect.mY < HEIGHT){
			mRect.mY++;
			mLastMove = DOWN;
		}
	}

public:
	char mGFX;

	Player() : mGFX('p')
	{
		setType(PLAYER);
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

	void handleCollision(const Entity& e)
	{
		if(e.mType == WALL){
			moveBack();
		}
	}

	void paint()	
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}
} player;

#endif
