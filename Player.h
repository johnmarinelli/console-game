#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Globals.h"
#include "LastMove.h"

#include <sstream>

class Player : public Entity
{
private:
	Statistics mStatistics;
	LastMove mLastMove;

	void moveBack()
	{
		switch(mLastMove){
			case UP: mRect.mY++; break;
			case DOWN: mRect.mY--; break;
			case LEFT: mRect.mX++; break;
			case RIGHT: mRect.mX--; break;
			case NONE: mRect.mX = 1; mRect.mY = 1; break;
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

	Player() : mGFX('p'), mLastMove(LASTMOVE_NONE)
	{
		setType(PLAYER);
		setRect(1,1,1,1);
		mStatistics.Health = 10;
	}
	
	//debug
	void moveback()
	{
		moveBack();
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

		std::stringstream ss;
		ss << "Player attacks " << e.mGFX << " for " << mStatistics.Damage;
		globalOutputs.push(ss.str());
	}

	void receiveMessage(MessageType type, const Statistics& stats)
	{
		switch(type)
		{	
			case MESSAGETYPE_ATTACK: mStatistics.Health -= stats.Damage;
				break;
			default:
				break;
		}	
	}
	
	bool isActive()
	{
		return true;
	}

	const Statistics& getStatistics()
	{
		return mStatistics;
	}

} player;

#endif
