#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include "Entity.h"

class HealthPack : public Entity
{
private:
	unsigned int mHealth;

	void giveHealth(Statistics& stats)
	{
		stats.Health += mHealth;
	
		mHealth = 0;
	}

public:
	char mGFX;

	HealthPack() : mHealth(1), mGFX('@')
	{
	}

    void handleCollision(Entity& e)
    {
        if(e.mType == ENEMY || e.mType == PLAYER){
			giveHealth(const_cast<Statistics&>(e.getStatistics()));
        }
    }

	void receiveMessage(MessageType type, Entity& sender)
	{
		if(type == MESSAGETYPE_GETHEALTH){
			giveHealth(const_cast<Statistics&>(sender.getStatistics()));
		}
	}
	
	bool isActive()
	{
		return (mHealth > 0);
	}

	void paint()
	{
	    moveTo(mRect.mX, mRect.mY);
        printf("%c", mGFX);
	}
};

#endif
