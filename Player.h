#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Globals.h"
#include "Statistics.h"

class Player : public Entity
{
private:
	Statistics mStatistics;

	enum LastMove{ NONE, UP, DOWN, LEFT, RIGHT } mLastMove;

	void moveBack()
	{
		switch(mLastMove){
			case UP: mRect.mY++; break;
			case DOWN: mRect.mY--; break;
			case LEFT: mRect.mX++; break;
			case RIGHT: mRect.mX--; break;
			default: break;
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

	void handleCollision(Entity& e)
	{
		if(e.mType == WALL){
			moveBack();
		}
		
		else if(e.mType == ENEMY){
			attack(e);
			moveBack();
		}
	}

	void paint()	
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}

	void attack(Entity& e)
	{
		e.receiveMessage(MESSAGETYPE_ATTACK, *this);
	}
	
	bool isActive()
	{
		return true;
	}

} player;

#endif
