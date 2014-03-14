#ifndef STATISTICS_H
#define STATISTICS_H

#include "Inventory.h"

struct Statistics
{
	//Inventory will hold the loot that entity holds
	Inventory inventory;

	int Health;
	int Damage;

	Statistics() : Health(1), Damage(1)
	{
	}
};

#endif
