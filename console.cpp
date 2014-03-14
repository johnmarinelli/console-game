#include <cstdio>
#include <iostream>
#include <string>

#include "CollisionSystem.h"
#include "QuadTree.h"
#include "EntityManager.h"
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"

int iscollision = 0;

void drawMap()
{
	std::cout << CLEAR_SCREEN;
	std::cout << MOVE_TO_0_0;
	int rows = HEIGHT;
	int cols = WIDTH;

	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			printf(".");	
		}
		printf("\n");
	}
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
	printf("\033[%d;%df", 2, borderXMargin); printf("SWAG");
	printf("\033[%d;%df", 3, borderXMargin); printf("collision: %d", iscollision);
}

int main()
{
	std::cout << CLEAR_SCREEN;	
	char input = ' ';

	EntityManager em;
	CollisionSystem cs(em);

	Wall wall;
	wall.setRect(5,5,1,1);

	Enemy enemy;
	
	em.add(&player);
	em.add(&wall);
	em.add(&enemy);

	drawMap();
	drawGUIBorder();
	drawGUI();
	em.paint();

	moveToInputArea();

	while(input != 'q'){
		std::cin >> input;
		std::cout << CLEAR_LINE;

		player.handleInput(input);

		cs.update(iscollision);
		em.update();

		drawMap();
		em.paint();
		drawGUIBorder();	
		drawGUI();

		moveToInputArea();
	}
	
	std::cout << MOVE_TO_0_0;

	return 0;
}
