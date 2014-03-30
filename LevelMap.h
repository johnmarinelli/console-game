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
