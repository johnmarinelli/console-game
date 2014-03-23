#ifndef MAP_H
#define MAP_H
#include "../Globals.h"
#include "Utilities.h"
#include "Room.h"
#include "Hallway.h"

#include <vector>

const int GRID_WIDTH = 2;
const int GRID_HEIGHT = 1;
class Map
{
private:
	std::vector<Rectangle> mGrid;
	std::vector<Room> mRooms;
	std::vector<Hallway> mHallways;

	void connectRooms()
	{
	    for(auto room = mRooms.begin(); room != mRooms.end() - 1; ++room)
	    {
	        auto neighbor = room + 1;
	        mHallways.push_back(connect(*room, *neighbor));
	        (*room).mIsConnected = true;
	    }
	}

	void initGFX()
	{
		//int mapwidth = mRooms[3].mRect.mX + mRooms.mRect.mWidth;
	}

public:
	Map()
	{
		int cellwidth = WIDTH / GRID_WIDTH;
		int cellheight = HEIGHT / GRID_HEIGHT;

		std::cout << cellwidth << " " << cellheight;
		//create grid
	    mGrid.push_back(Rectangle(1, 1, cellwidth, cellheight));
	    mGrid.push_back(Rectangle(cellwidth, 1, cellwidth, cellheight));
	    mGrid.push_back(Rectangle(cellwidth*2, 1, cellwidth, cellheight));
	    mGrid.push_back(Rectangle(cellwidth*3, 1, cellwidth, cellheight));

		//create rooms from grid
	    for(int i = 0; i < MAX_ROOMS; ++i){
	        mRooms.push_back(createRandomRoom(mGrid[i]));
	    }

    	//create halls from rooms
    	connectRooms();
	}	

	void draw()
	{
		std::cout << CLEAR_SCREEN;
	
/*		for(auto& room : mRooms){
   		    room.draw();
   		}

  		for(auto& hall : mHallways){
   	    	hall.draw();
   		}*/
		
		//mRooms[0].drawgfx();
		//mRooms[0].draw();

		for(auto& room: mRooms){ room.drawgfx(); }
		for(auto& hall : mHallways){ hall.drawgfx(); }
	}
};

#endif
