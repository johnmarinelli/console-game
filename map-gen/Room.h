#ifndef ROOM_H
#define ROOM_H

#include "../Rectangle.h"
#include "Vector2D.h"

#include <vector>
#include <array>
#include <random>

const int MAX_ROOMS = 4;

const int MIN_ROOM_DIMENSION = 3;
const int MIN_ROOM_HEIGHT = HEIGHT - 3;
const int MAX_ROOM_WIDTH = WIDTH / (MAX_ROOMS);
const int MAX_ROOM_HEIGHT = HEIGHT - 1;

const char WALL_CHAR = '+';
const char FLOOR_CHAR = '.';

int indexAt(int x, int y, int width)
{
	return (x * width) + y;
}

/*WALLS ARE EXTENDED HORIZONTALLY*/
struct Room
{
private:
	char **mGFX;
	int mGFXHeight, mGFXWidth;
		
	void initGFX()
	{
		int gfxHeight = mRect.mHeight + 1;
		int gfxWidth = mRect.mWidth + 1;

		mGFXHeight = gfxHeight;
		mGFXWidth = gfxWidth;

		//+1 because onscreen is index 1 
		mGFX = new char*[gfxHeight];
	
		//+1 because onscreen is index 1
		for(int i = 0; i < gfxHeight; ++i){
			mGFX[i] = new char[gfxWidth];
		}

		for(int row = 0; row < gfxHeight; ++row){
			for(int col = 0; col < gfxWidth; ++col){
				char c = FLOOR_CHAR;
				if(row == 0 || row == gfxHeight - 1) c = WALL_CHAR;
				if(col == 0 || col == gfxWidth - 1) c = WALL_CHAR;
				mGFX[row][col] = c;
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

	/*
	* right wall will be the last column of the width
	* bottom wall will be the last row of the height
	*/
	Room(int x, int y, int width, int height) : mRect(x, y, width, height), mIsConnected(false)
	{
		//top wall
		mWalls.push_back(Rectangle(x, y, width, 1));
	
		//right wall
		mWalls.push_back(Rectangle(x + width, y, 1, height));

		//bottom wall, extended to meet with right wall corner
		mWalls.push_back(Rectangle(x, y + height, width + 1, 1));
		
		//left wall
		mWalls.push_back(Rectangle(x, y, 1, height));

		initGFX();
	}

	virtual void draw()
	{
		std::cout << MOVE_TO_0_0;
	
		//draw floor
		drawRect(mRect, FLOOR_CHAR);

		std::cout << MOVE_TO_0_0;

		//draw walls	
		for(auto& wall : mWalls){
			drawRect(wall, WALL_CHAR);	
		}
	}

	void drawgfx()
	{
		int row = 0, col = 0;
		for(row = 0; row < mGFXHeight; ++row){
			for(col = 0; col < mGFXWidth; ++col){
				moveTo(mRect.mX + col, mRect.mY + row);
				printf("%c", mGFX[row][col]);
            }
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

	std::uniform_int_distribution<int> rheight(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);
	int height = rheight(reng);

	std::uniform_int_distribution<int> rx(gridCell.mX, gridCell.mX + gridCell.mWidth / 2);
	int x = rx(reng);

	std::uniform_int_distribution<int> ry(gridCell.mY, gridCell.mY + 1);
	int y = ry(reng);

	return Room(x, y, width, height);
}

#endif
