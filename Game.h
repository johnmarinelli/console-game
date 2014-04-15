#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <iostream>
#include <string>

#include "CollisionSystem.h"
#include "QuadTree.h"
#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "HealthPack.h"

#include "LevelMap.h"
#include "Stairs.h"
#include "Gui.h"

class Game
{
private:

	void initMap()
	{
		runMapGenerator();
		std::ifstream gfx("map-gen/map.txt");
		std::ifstream info("map-gen/mapinfo.txt");
	
		mLevelMap.init(gfx, info, true);

		gfx.close();
		info.close();
	}

	struct Stage
	{
		unsigned int Level; 
	
		Stairs DownStairs;
	
		Stage() : Level(1)
		{
		}

	} mStage;
	
	EntityManager mEntityManager;
	CollisionSystem mCollisionSystem;
	LevelMap mLevelMap;
	Player mPlayer;
	Gui mGui;
	HealthPack healthpack;
	Enemy mEnemies[10];

	char mInput;
	
	void spawnEnemies()
	{
		int minLevel = mStage.Level > 3 ? mStage.Level - 3 : mStage.Level;
		int maxLevel = mStage.Level;		

		int enemies = mStage.Level > 4 ? mStage.Level : 4;

		for(int i = 0; i < enemies; ++i){
			int level = getRandomNumber(minLevel, maxLevel) + ASCII_DIFFERENCE;

			int roomNo = i % 4;

			Enemy enemy(Rectangle(), level);

			mEnemies[i] = enemy;
			mLevelMap.insertInto(mEnemies[i], roomNo);
			mEntityManager.add(&mEnemies[i]);
		}
	}

public:
	Game() : mInput(' '), mCollisionSystem(mEntityManager)
	{
		initMap();

		mLevelMap.insertInto(healthpack, 0);
		mLevelMap.insertInto(mPlayer, 0);

		mEntityManager.add(&mPlayer);
		mEntityManager.add(&healthpack);
		
		mLevelMap.insertInto(mStage.DownStairs, 3);
	
		mEntityManager.add(&(mStage.DownStairs));

		spawnEnemies();
	}

	void update()
	{
		while(mInput != 'q'){
			if(mEntityManager.enemies() < 4){
				reset();
			}	
	
			std::cin >> mInput;
			std::cout << CLEAR_LINE;

			mPlayer.handleInput(mInput);

			mCollisionSystem.update(mLevelMap);
			mEntityManager.update();

			mGui.drawMap(mLevelMap);
			mEntityManager.paint();
			mGui.writeOutput(mPlayer.getStatistics(), mPlayer);
			
			moveToInputArea();
		}
	}

	void reset()
	{
		mEntityManager.reset();
		mCollisionSystem.reset();
		mLevelMap.reset();

		mStage.Level = mStage.Level > 26 ? mStage.Level : mStage.Level + 1;

		initMap();

		mLevelMap.insertInto(mPlayer, 0);			
		mLevelMap.insertInto(healthpack, 0);

		mEntityManager.add(&mPlayer);
		mEntityManager.add(&healthpack);
		
		mLevelMap.insertInto(mStage.DownStairs, 3);
	
		mEntityManager.add(&(mStage.DownStairs));

		spawnEnemies();
	}
};

#endif
