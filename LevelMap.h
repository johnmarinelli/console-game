#ifndef LEVELMAP_H
#define LEVELMAP_H

#include "map-gen/Map.h"
#include <iostream>
#include <string>

class LevelMap : public Map
{
private:
	char **mGFX;
	int mHeight;
	int mWidth;

	void getInfo(std::ifstream& info)
	{
		info >> mWidth;
		info >> mHeight;
	}

	/*
	*  column-major
	*/
	void getGFX(std::ifstream& gfx)
	{
		//txt file is index 1
		mWidth++;
		mHeight++;

		mGFX = new char*[mHeight];

		for(int i  = 0; i < mHeight; i++){
			mGFX[i] = new char[mWidth];
		}

		int rowN = 0, colN = 0;
		char c;
		
		while(gfx.get(c) && rowN < mHeight){
			mGFX[rowN][colN] = c;

			if(colN == mWidth){
				colN = 0;
				rowN++;
			}
	
			colN++;
		}

		/*for(; rowN < mHeight; ++rowN){
			for(; colN < mWidth; ++colN){
				gfx.get(c);
				mGFX[rowN][colN] = c;
			}
		}*/
	}

public:
	LevelMap() : mHeight(0), mWidth(0) 
	{
	}
	
	void init(std::ifstream& gfx, std::ifstream& info)
	{
		getInfo(info);
		getGFX(gfx);
	}

	bool isValidMove(int x, int y)
	{
		return (mGFX[y-1][x] != WALL_CHAR && mGFX[y-1][x-1] != ' ');
	}
	
	void draw()
	{
		for(int row = 0; row < mHeight; row++){
			for(int col = 0; col < mWidth; col++){
				printf("%c", mGFX[row][col]);
			}
		}
	}
};

#endif
