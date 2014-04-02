#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <iostream>
#include <string>

#include "CollisionSystem.h"
#include "QuadTree.h"
#include "EntityManager.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"

#include "LevelMap.h"

int iscollision = 0;

void drawMap(LevelMap& map)
{
    std::cout << CLEAR_SCREEN;
    std::cout << MOVE_TO_0_0;

    map.draw();
}

void drawGUIBorder()
{
    int borderXMargin = WIDTH + 4;
    std::cout << MOVE_TO_0_0;

    for(int i = 1; i < HEIGHT + 1; ++i){
        printf("\033[%d;%df", i, borderXMargin); printf("|");
    }
}

void drawGUI()
{
    int borderXMargin = WIDTH + 7;
    std::cout << MOVE_TO_0_0;

    printf("\033[%d;%df", 1, borderXMargin); printf("INVENTORY");
    printf("\033[%d;%df", 3, borderXMargin); printf("collision: %d", iscollision);
}

void writeOutput()
{
    std::cout << MOVE_TO_0_0;

    moveTo(0, HEIGHT + 1);

    while(!globalOutputs.empty()){
        std::cout << globalOutputs.front() << std::endl;
        globalOutputs.pop();
    }
}

class Game
{
private:
	EntityManager mEntityManager;
	CollisionSystem mCollisionSystem;
	LevelMap mLevelMap;
	Player mPlayer;
	Enemy mEnemy;

	char mInput;
	
public:
	Game() : mInput(' '), mCollisionSystem(mEntityManager)
	{
		std::ifstream gfx("map-gen/map.txt");
		std::ifstream info("map-gen/mapinfo.txt");
	
		mLevelMap.init(gfx, info);
		mLevelMap.insertInto(mEnemy, 0);

		mPlayer.setRect(14, 3, 1, 1);

		mEntityManager.add(&mPlayer);
		mEntityManager.add(&mEnemy);
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

			drawMap(mLevelMap);
			mEntityManager.paint();
			writeOutput();
		
			moveToInputArea();
		}
	}

};

#endif
