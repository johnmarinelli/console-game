#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Globals.h"
#include "LastMove.h"

#include <sstream>

/*
* 97 is the ascii value for 'a', so we use mGFX - ASCII_DIFFERENCE to determine level
*/ 
const int ASCII_DIFFERENCE = 96;

class Enemy : public Entity
{
private:
	Statistics mStatistics;
	
	bool inRange(Rectangle& rect)
	{
		int distanceX = std::abs(rect.mX - mRect.mX);
		int distanceY = std::abs(rect.mY - mRect.mY);
		
		if(distanceX < 2 && distanceY < 2){
			return true;
		}

		else{
			return false;
		}
	}

	class AI
	{
	private:
		Enemy& mBody;
		LastMove mLastMove;
		
		void moveToward(const Rectangle& target)
		{
			Rectangle& rect = mBody.mRect;
			
			if(rect.mX > target.mX+1){
				rect.mX--;
				mLastMove = LEFT;
			}
			else if(rect.mX < target.mX-1){
				rect.mX++;
				mLastMove = RIGHT;
			}
			
			else if(rect.mY > target.mY+1){
				rect.mY--;
				mLastMove = UP;
			}
			else if(rect.mY < target.mY-1){
				rect.mY++;	
				mLastMove = DOWN;
			}
		}

	public:
		friend class Enemy;
	
		enum AIState { IDLE, WANDER, ATTACK } mState;
		
		AI(Enemy& body) : mState(IDLE), mBody(body)
		{
		}

		AIState getState()
		{
			return mState;
		}

		void setState(AIState state)
		{
			mState = state;
		}

		void update()
		{
			switch(mState)
			{
				case IDLE:
					break;
				case WANDER:
					break;
				case ATTACK: moveToward(mBody.mTarget->mRect);
							 mBody.attack(*(mBody.mTarget));
					break;
			}
		}

		void moveBack()
		{
			Rectangle& rect = mBody.mRect;
			switch(mLastMove)
			{
				case UP: rect.mY++;
					break;
				case DOWN: rect.mY--;
					break;
				case LEFT: rect.mX++;
					break;
				case RIGHT: rect.mX--;
					break;
				default: break;
			}
		}	
	} mAI;

	Entity* mTarget;

public:
	char mGFX;
	unsigned int mLevel;

	Enemy() : mGFX('a'), mAI(*this), mTarget(nullptr), mLevel(mGFX - ASCII_DIFFERENCE)
	{
		setType(ENEMY);
		setRect(2,2,2,2);
	}

	Enemy(Rectangle rect, char level) : mGFX(level), mAI(*this), mTarget(nullptr), mLevel(mGFX - ASCII_DIFFERENCE)
	{
		setRect(rect.mX, rect.mY, rect.mWidth, rect.mHeight);
		setType(ENEMY);
	}

	Enemy(const Enemy& e) : mGFX(e.mGFX), mAI(*this), mTarget(e.mTarget), mLevel(e.mLevel)
	{
		setRect(e.mRect);
		setType(ENEMY);
	}

	Enemy& operator=(const Enemy& e)
	{		
		mGFX = e.mGFX;
		
		mTarget = nullptr;
		mLevel = e.mLevel;

		setRect(e.mRect);
		setType(ENEMY);

		return *this;
	}

	void handleCollision(Entity& e)
	{
		if(e.mType == PLAYER){
			attack(e);
		}
	}

	void update()
	{
		mAI.update();
	}

	void moveBack()
	{
		mAI.moveBack();
	}
	
	void paint()
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}

	void attack(Entity& e)
	{	
		if(inRange(e.mRect)){
			e.receiveMessage(MESSAGETYPE_ATTACK, mStatistics);

			std::stringstream ss;
			ss << mGFX << " hits Player for " << mStatistics.Damage;
			globalOutputs.push(ss.str());
		}
	}

	void receiveMessage(MessageType type, Entity& sender)
	{
		switch(type)
        {
            case MESSAGETYPE_ATTACK: mStatistics.Health -= sender.getStatistics().Damage;
									 mAI.setState(AI::AIState::ATTACK);
									 mTarget = &sender;
                break;
            default: 
				break;
        }
	}

	bool isActive()
	{
		bool isactive = (mStatistics.Health > 0);

		if(!isactive){
			std::stringstream ss;
			ss << "Player defeated " << mGFX << ".";
			globalOutputs.push(ss.str());
		}

		return isactive;
	}

	void reset()
	{
		mTarget = nullptr;
		mAI.setState(AI::AIState::IDLE);
		mStatistics.Health = 4;
	
		mLevel = 0;
	}

	~Enemy()
	{
		reset();
	}
};

#endif
