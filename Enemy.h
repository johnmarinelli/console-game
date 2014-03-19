#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Globals.h"
#include "LastMove.h"

#include <sstream>

class Enemy : public Entity
{
private:
	Statistics mStatistics;

	class AI
	{
	private:
		Enemy& mBody;
		LastMove mLastMove;
		
		void moveToward(const Rectangle& target)
		{
			Rectangle& rect = mBody.mRect;
			
			if(rect.mX > target.mX){
				rect.mX--;
				mLastMove = LEFT;
			}
			else if(rect.mX < target.mX){
				rect.mX++;
				mLastMove = RIGHT;
			}
			
			if(rect.mY > target.mY){
				rect.mY--;
				mLastMove = UP;
			}
			else if(rect.mY < target.mY){
				rect.mY++;	
				mLastMove = DOWN;
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
							 moveBack();
					break;
			}
		}
	} mAI;

	Entity* mTarget;

public:
	char mGFX;

	Enemy() : mGFX('a'), mAI(*this), mTarget(nullptr)
	{
		setType(ENEMY);
		setRect(2,2,2,2);
	}

	Enemy(Rectangle rect, char level) : mGFX(level), mAI(*this), mTarget(nullptr)
	{
		setRect(rect.mX, rect.mY, rect.mWidth, rect.mHeight);
		setType(ENEMY);
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
	
	void paint()
	{
		moveTo(mRect.mX, mRect.mY);
		printf("%c", mGFX);
	}

	void attack(Entity& e)
	{	
		e.receiveMessage(MESSAGETYPE_ATTACK, mStatistics);

		std::stringstream ss;
		ss << mGFX << " hits Player for " << mStatistics.Damage;
		globalOutputs.push(ss.str());
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
};

#endif
