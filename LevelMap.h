#ifndef LEVELMAP_H
#define LEVELMAP_H

#include "map-gen/Map.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "LevelRoom.h"
#include "LevelHallway.h"

class LevelMap : public Map
{
private:
	char **mGFX;
	int mHeight;
	int mWidth;

	std::vector<LevelRoom*> mLevelRooms;
	std::vector<LevelHallway*> mLevelHallways;

	void getInfo(std::ifstream& info)
	{
		info >> mWidth;
		info >> mHeight;

		//console output is index 1, not 0
		mWidth++;
		mHeight++;

		std::string input;
		int x = 0, y = 0, width = 0, height = 0;
		bool isRoom = true;

		while(info)
		{
			std::getline(info, input);
		
			if(input.compare("Room") == 0){
				isRoom = true;
			}
	
			else if(input.compare("Hall") == 0){
				isRoom = false;
			}
		
			else if(input.compare("{") == 0){
				bool endBrace = false;
	
				Rectangle rect;

				while(!endBrace){			
					std::getline(info, input);
			
					if(input.compare("}") == 0){
						endBrace = true;
						break;
					}

					else
					{
						using namespace std;

						vector<string> split;
						stringstream ss(input);
						string row;
			
						while(getline(ss, row, ':')){
							split.push_back(row);
						}  //while

						if(split[0] == "x"){
							rect.mX = atoi(split[1].c_str());
						}
						else if(split[0] == "y"){
							rect.mY = atoi(split[1].c_str());
						}
						else if(split[0] == "width"){
							rect.mWidth = atoi(split[1].c_str());
						}
						else if(split[0] == "height"){
							rect.mHeight = atoi(split[1].c_str());
						}
					}  //else		
				}  //while(!endBrace)

				if(isRoom){
					mLevelRooms.push_back(new LevelRoom(rect));
				}

				else{
					mLevelHallways.push_back(new LevelHallway(rect));
				}
			}  //else if("{")
			
			else if (input.compare("\n")){
			}
		
			else{
			}
		}  //while
	}  //getInfo

	/*
	*  column-major
	*/
	void getGFX(std::ifstream& gfx)
	{
		//txt file is index 1
		/*mWidth++;
		mHeight++;

		mGFX = new char*[mHeight];

		for(int i  = 0; i < mHeight; i++){
			mGFX[i] = new char[mWidth];
		}*/

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
	}

	void resetGFX()
	{
		//we reuse the memory allocated the first time.
		for(int i = 0; i < mHeight; ++i){
			for(int j = 0; j < mWidth; ++j){
				mGFX[i][j] = ' ';
			}
		}
	}

public:
	LevelMap() : mHeight(0), mWidth(0) 
	{
	}
	
	void init(std::ifstream& gfx, std::ifstream& info)
	{
		getInfo(info);

		//allocate once, reuse object for every level
		mGFX = new char*[mHeight];

		for(int i  = 0; i < mHeight; i++){
			mGFX[i] = new char[mWidth];
		}

		getGFX(gfx);
	}

	/*
	* check whether point at mGFX is an invalid tile
	* y-2 is because there is two rows of difference between player coordinates & mGFX coordinates
	*/
	const bool isValidMove(int x, int y) const
	{
		return (mGFX[y-2][x] != WALL_CHAR && mGFX[y-2][x] != ' ');
	}
	
	void draw()
	{
		for(int row = 0; row < mHeight; row++){
			for(int col = 0; col < mWidth; col++){
				printf("%c", mGFX[row][col]);
			}
		}
	}

	void insertInto(Entity& e, const int roomNo = -1)
	{
		if(roomNo > -1 && roomNo < mLevelRooms.size()){
			Rectangle rect = mLevelRooms[roomNo]->mRect;
			int x = getRandomNumber(rect.mX + 1, rect.mX + rect.mWidth - 2);
		
			//difference of 3 and 2 because on screen coordinates are different
			int y = getRandomNumber(rect.mY + 3, rect.mY + rect.mHeight - 2);

			e.setRect(x, y, 1, 1);

			mLevelRooms[roomNo]->add(e);
		}
	}
	
	void reset()
	{
		for(auto& room : mLevelRooms){
			delete room;
			room = nullptr;
		}
		
		mLevelRooms.clear();
	
		for(auto& hall : mLevelHallways){
			delete hall;
			hall = nullptr;
		}
	
		mLevelHallways.clear();

		resetGFX();
	}

	~LevelMap()
	{
		for(int i = 0; i < mHeight; i++){
			delete []mGFX[i];
		}
			
		delete []mGFX;
	}
};

#endif
