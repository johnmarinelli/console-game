#include <cstdio>
#include <iostream>
#include <string>

#include "QuadTree.h"
#include "EntityManager.h"
#include "Player.h"

int iscollision = 0;

void drawMap()
{
	std::cout << CLEAR_SCREEN;
	std::cout << MOVE_TO_0_0;
	int rows = HEIGHT;
	int cols = WIDTH;

	for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			printf("-");	
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

void collision(QuadTree& qt, EntityManager& em)
{
	std::vector<Entity*> v;	

	for(int i = 0; i < em.size(); i++){
		v.clear();
		qt.getObjects(v, em[i]->mRect);

		for(int j = 0; j < v.size(); j++){
			if(v[j] != em[i]){
				if(checkCollision(*em[i], *v[j])){
					iscollision++;
				}
			}
		}
	}
}

int main()
{
	std::cout << CLEAR_SCREEN;	
	char input = ' ';

	QuadTree qt(0, Rectangle(0, 0, WIDTH, HEIGHT));
	EntityManager em;

	qt.insert(&player);
	em.add(&player);

	drawMap();
	drawGUIBorder();
	drawGUI();
	moveToInputArea();

	//em.paint();
	qt.display();

	//TODO: implement an attack system
	while(input != 'q'){
		std::cin >> input;
		std::cout << CLEAR_LINE;

		player.handleInput(input);

		collision(qt, em);

		drawMap();
		em.paint();
		drawGUIBorder();	
		drawGUI();

		moveToInputArea();
	}
	
	std::cout << MOVE_TO_0_0;

	return 0;
}
