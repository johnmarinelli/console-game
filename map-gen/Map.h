#ifndef MAP_H
#define MAP_H
#include "../Globals.h"
#include "Utilities.h"
#include "Room.h"
#include "Hallway.h"

#include <vector>

#include <fstream>

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

public:
	Map()
	{
		int cellwidth = WIDTH / GRID_WIDTH;
		int cellheight = HEIGHT / GRID_HEIGHT;

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
		for(auto& room: mRooms){ room.drawGFX(); }
		for(auto& hall : mHallways){ hall.drawGFX(); }
	}

	void toFile(std::ofstream& outfile)
	{
		for(auto& room : mRooms){
			outfile << "Room\n";
			outfile << "{\n";
			outfile << "x: " << room.mRect.mX << "\n";
			outfile << "y: " << room.mRect.mY << "\n";
			outfile << "width: " << room.mRect.mWidth << "\n";
			outfile << "height: " << room.mRect.mHeight << "\n";
			outfile << "}\n\n";
		}

		for(auto& hall : mHallways){
			outfile << "Hall\n";
			outfile << "{\n";
			outfile << "x: " << hall.mRect.mX << "\n";
			outfile << "y: " << hall.mRect.mY << "\n";
			outfile << "width: " << hall.mRect.mWidth << "\n";
			outfile << "height: " << hall.mRect.mHeight << "\n";
			outfile << "}\n\n";
		}
	}
};

#endif
