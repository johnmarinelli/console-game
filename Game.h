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
#include "Gui.h"

class Game
{
private:

	struct Stage
	{
		unsigned int Level; 
		unsigned int Enemies;
	
		Stage() : Level(1), Enemies(0)
		{
		}

	} mStage;
	
	EntityManager mEntityManager;
	CollisionSystem mCollisionSystem;
	LevelMap mLevelMap;
	Player mPlayer;
	Gui mGui;
	HealthPack healthpack;
	//std::vector<Enemy> mEnemies;

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

			Enemy enemy;

			mEnemies[i] = enemy;
			mLevelMap.insertInto(mEnemies[i], roomNo);
			mEntityManager.add(&mEnemies[i]);
//			mEnemies.push_back(enemy);
//			mLevelMap.insertInto(mEnemies.back(), roomNo);
//			mEntityManager.add(&(mEnemies.back()));
		}
	}

public:
	Game() : mInput(' '), mCollisionSystem(mEntityManager)
	{
		std::ifstream gfx("map-gen/map.txt");
		std::ifstream info("map-gen/mapinfo.txt");
	
		mLevelMap.init(gfx, info);

		mPlayer.setRect(14, 4, 1, 1);

		mLevelMap.insertInto(healthpack, 0);

		mEntityManager.add(&mPlayer);
		mEntityManager.add(&healthpack);

		spawnEnemies();
	}

	void update()
	{
		while(mInput != 'q'){
			std::cin >> mInput;
			std::cout << CLEAR_LINE;

			mPlayer.handleInput(mInput);

			if(!mLevelMap.isValidMove(mPlayer.mRect.mX, mPlayer.mRect.mY)){
				mPlayer.moveback();
			}
		
			mCollisionSystem.update();
			mEntityManager.update();

			mGui.drawMap(mLevelMap);
			mEntityManager.paint();
			mGui.writeOutput(mPlayer.getStatistics(), mPlayer);
		
			moveToInputArea();
		}
	}
};

#endif
