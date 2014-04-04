#ifndef HEALTHPACK_H
#define HEALTHPACK_H

#include "Entity.h"
#include "Statistics.h"

class HealthPack : public Entity
{
private:
	void giveHealth(Statistics& stats)
	{
		stats.Health += mStatistics.Health;

		std::stringstream ss;
        ss << "Player picks up some health.";
        globalOutputs.push(ss.str());

		mStatistics.Health = 0;
	}

public:
	char mGFX;
	Statistics mStatistics;

	HealthPack() : mGFX('@'), mStatistics(1, 0, 0)
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
		return (mStatistics.Health > 0);
	}

	void paint()
	{
	    moveTo(mRect.mX, mRect.mY);
        printf("%c", mGFX);
	}
};

#endif
