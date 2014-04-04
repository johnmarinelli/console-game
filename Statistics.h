#ifndef STATISTICS_H
#define STATISTICS_H

#include "Inventory.h"

/*
*  This holds extra information about an entity
*/

struct Statistics
{
	//Inventory will hold the loot that entity holds
	Inventory inventory;

	int Health;
	int Damage;

	unsigned int Experience;

	Statistics() : Health(4), Damage(1), Experience(0)
	{
	}
	
	Statistics(int health, int damage, int exp) : Health(health), Damage(damage), Experience(exp)
	{
	}
};

#endif
