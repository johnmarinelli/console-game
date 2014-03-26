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

int main()
{
	//std::cout << CLEAR_SCREEN;	
	char input = ' ';

	EntityManager em;
	CollisionSystem cs(em);

	Wall wall;
	wall.setRect(5,5,1,1);

	Enemy enemy;
	
	em.add(&player);
	em.add(&wall);
	em.add(&enemy);

	//i know 13, 3 to be valid floor
	player.setRect(14, 3, 1, 1);

	//call map generating program
	int success = system("./map-gen/mg");
	
	/*lol fix this*/
	while(success == 35584) {
		success = system("./map-gen/mg");
//		printf("map gen failed: %d\n", success);
//		return 0;
	}

	LevelMap levelmap;
	std::ifstream gfx("map-gen/map.txt");
	std::ifstream info("map-gen/mapinfo.txt");
	levelmap.init(gfx, info);

	levelmap.draw();

	std::cout << "Press any key to start" << std::endl;
	moveToInputArea();

	while(input != 'q'){
		std::cin >> input;
		std::cout << CLEAR_LINE;

		player.handleInput(input);

		if(!levelmap.isValidMove(player.mRect.mX, player.mRect.mY))	
			player.moveback();

		cs.update(iscollision);
		em.update();

		drawMap(levelmap);
		em.paint();
		writeOutput();

		moveToInputArea();
	}

	std::cout << MOVE_TO_0_0;

	return 0;
}
