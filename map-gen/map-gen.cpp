#include "../Globals.h"
#include "Utilities.h"
#include "Room.h"
#include "Hallway.h"

#include <vector>

const int GRID_WIDTH = 2;
const int GRID_HEIGHT = 2;

std::vector<Rectangle> grid;
std::vector<Room> rooms;
std::vector<Hallway> hallways;

void connectRooms()
{
	for(auto& room : rooms)
	{
		Rectangle original = room.mRect;
		Room& neighbor = findNearestNeighbor(room, rooms);
		room.mRect = original;

		hallways.push_back(static_cast<Hallway>(room.connect(neighbor)));
	}
}

void drawMap()
{
	std::cout << CLEAR_SCREEN;
	
	for(auto& hall : hallways){
		hall.draw();
	}
	for(auto& room : rooms){
		room.draw();	
	}
	
}

int main(int argc, char* args[])
{
	int cellwidth = WIDTH / GRID_WIDTH;
	int cellheight = HEIGHT / GRID_HEIGHT;

	grid.push_back(Rectangle(1, 1, cellwidth, cellheight));
	grid.push_back(Rectangle(cellwidth, 1, cellwidth, cellheight));
	grid.push_back(Rectangle(cellwidth, cellheight, cellwidth, cellheight));
	grid.push_back(Rectangle(1, cellheight, cellwidth, cellheight));

	for(int i = 0; i < MAX_ROOMS; ++i){
		rooms.push_back(createRandomRoom(grid[i]));
	}
	
//	std::cout << "cell width: " << cellwidth << std::endl;

//	std::cout << "cell height: " << cellheight << std::endl;

	connectRooms();

	drawMap();
	
	char c;
	std::cin >> c;

	std::cout << CLEAR_SCREEN;
	return 0;
}
