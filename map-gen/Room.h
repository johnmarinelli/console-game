#ifndef ROOM_H
#define ROOM_H

#include "../Rectangle.h"
#include "Vector2D.h"

#include <vector>
#include <random>

#include <cmath>

const int MAX_ROOMS = 4;

const int MIN_ROOM_DIMENSION = 4;
const int MIN_ROOM_HEIGHT = HEIGHT - 3;
const int MAX_ROOM_WIDTH = WIDTH / (MAX_ROOMS);
const int MAX_ROOM_HEIGHT = HEIGHT - 1;

const char WALL_CHAR = '+';
const char FLOOR_CHAR = '.';

int indexAt(int x, int y, int width)
{
	return (x * width) + y;
}

struct Room
{
private:
	char **mGFX;

	void initGFX()
	{
		int gfxHeight = mRect.mHeight;
		int gfxWidth = mRect.mWidth;

		mGFXHeight = gfxHeight;
		mGFXWidth = gfxWidth;
 
		mGFX = new char*[gfxHeight];
	
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
	int mGFXHeight, mGFXWidth;
	
	std::vector<Rectangle> mWalls;

	Room() : mRect(), mIsConnected(false), mGFXHeight(0), mGFXWidth(0)
	{
	}
	
	Room(const Room& c) : mRect(c.mRect), mIsConnected(c.mIsConnected), mGFXHeight(c.mGFXHeight), mGFXWidth(c.mGFXWidth), mWalls(c.mWalls)
	{	
		//+1 because onscreen is index 1 
		mGFX = new char*[mGFXHeight];
	
		//+1 because onscreen is index 1
		for(int i = 0; i < mGFXHeight; ++i){
			mGFX[i] = new char[mGFXWidth];
		}

		for(int row = 0; row < mGFXHeight; ++row){
			for(int col = 0; col < mGFXWidth; ++col){
				mGFX[row][col] = c.mGFX[row][col];
			}
		}
	}

	/*
	* right wall will be the last column of the width
	* bottom wall will be the last row of the height
	* extends collision rectangle accordingly
	*/
	Room(int x, int y, int width, int height) : mRect(x, y, width, height), mIsConnected(false), mGFXWidth(width), mGFXHeight(height)
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
	
	Room(const Rectangle& rect) : mRect(rect), mIsConnected(false), mGFXWidth(rect.mWidth), mGFXHeight(rect.mHeight)
	{
		//top wall
		mWalls.push_back(Rectangle(rect.mX, rect.mY, rect.mWidth, 1));
	
		//right wall
		mWalls.push_back(Rectangle(rect.mX + rect.mWidth, rect.mY, 1, rect.mHeight));

		//bottom wall, extended to meet with right wall corner
		mWalls.push_back(Rectangle(rect.mX, rect.mY + rect.mHeight, rect.mWidth + 1, 1));
		
		//left wall
		mWalls.push_back(Rectangle(rect.mX, rect.mY, 1, rect.mHeight));

		initGFX();
	}

	virtual void draw() const
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

	void drawGFX()
	{
		int row = 0, col = 0;
		for(row = 0; row < mGFXHeight; ++row){
			for(col = 0; col < mGFXWidth; ++col){
				moveTo(mRect.mX + col, mRect.mY + row);
				printf("%c", mGFX[row][col]);
            }
        }
	}

	bool setGFX(char c, int y, int x)
	{
		if(std::abs(y) > 1000){
			return false;
		}
		mGFX[y][x] = c;
return true;
	}	

	/*
	* this function is used in Map::toFile, where the input will
	* be offset by the x and y position of the itr.
	* so, i subtract accordingly to position @ origin
	*/
	const char getGFX(int x, int y) const
	{
		int xCoord = x - mRect.mX;
		int yCoord = y - mRect.mY;

		return mGFX[yCoord][xCoord];
	}

	template <typename T>
	Vector2D<T> getRandomWall();

	virtual ~Room()
	{	
		for(int i = 0; i < mGFXHeight; ++i){
            delete []mGFX[i];
        }
	
		delete []mGFX;
	}
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

	//this is a bit of a hack; for the fourth room we have to check if it exceeds the
	//max amt width on (my) terminal, if it does then we just reduce the width of
    //the fourth room
	if(x + width > 177){
		int diff = x+width - 177;
		width -= diff;
	}
	
	return Room(x, y, width, height);
}

#endif
