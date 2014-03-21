#ifndef ROOM_H
#define ROOM_H

#include "../Rectangle.h"
#include "Vector2D.h"

#include <vector>
#include <random>

const int MAX_ROOMS = 4;

const int MIN_ROOM_DIMENSION = 3;
const int MAX_ROOM_WIDTH = WIDTH / (MAX_ROOMS + 3);
const int MAX_ROOM_HEIGHT = HEIGHT - 1;

const char WALL_CHAR = '+';
const char FLOOR_CHAR = '.';

struct Room
{
private:
	void drawRect(const Rectangle& rect, const char gfx)
	{
		int i = 0, j = 0;

		for(i = 0; i < rect.mHeight; ++i){
            moveTo(rect.mX, rect.mY + i);
            for(j = 0; j < rect.mWidth; ++j){
                printf("%c", gfx);
            }
        }
	}

public:
	Rectangle mRect;
	bool mIsConnected;
	
	std::vector<Rectangle> mWalls;

	Room() : mRect(), mIsConnected(false)
	{
	}

	Room(int x, int y, int width, int height) : mRect(x, y, width, height), mIsConnected(false)
	{
		//top wall
		mWalls.push_back(Rectangle(x, y, width + 1, 1));
	
		//right wall
		mWalls.push_back(Rectangle(x + width, y, 1, height));

		//bottom wall
		mWalls.push_back(Rectangle(x, y + height, width + 1, 1));
		
		//left wall
		mWalls.push_back(Rectangle(x, y, 1, height));
	}

	void draw()
	{
		std::cout << MOVE_TO_0_0;
		int i = 0, j = 0;
		
		//draw floor
		drawRect(mRect, FLOOR_CHAR);

		std::cout << MOVE_TO_0_0;

		//draw walls	
		for(auto& wall : mWalls){
			drawRect(wall, WALL_CHAR);	
		}
	}

	template <typename T>
	Vector2D<T> getRandomWall();
};

template <typename T>
Vector2D<T> getRandomWall()
{
}

static Room createRandomRoom(const Rectangle& gridCell)
{
	std::random_device rd;

	std::default_random_engine reng(rd());
	std::uniform_int_distribution<int> rwidth(MIN_ROOM_DIMENSION, MAX_ROOM_WIDTH);
	int width = rwidth(reng);

	std::uniform_int_distribution<int> rheight(MIN_ROOM_DIMENSION, MAX_ROOM_HEIGHT);
	int height = rheight(reng);

	std::uniform_int_distribution<int> rx(gridCell.mX, gridCell.mX + gridCell.mWidth);
	int x = rx(reng);

	std::uniform_int_distribution<int> ry(gridCell.mY, gridCell.mY + gridCell.mHeight);
	int y = ry(reng);

	return Room(x, y, width, height);
}

#endif
