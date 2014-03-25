#include "Map.h"

int main(int argc, char* args[])
{
	Map map;
	std::cout << CLEAR_SCREEN;
	map.draw();

	std::ofstream outfile("map.txt");
	
	if(outfile){
		map.gfxToFile(outfile);
	}

	char c;
	std::cin >> c;

	std::cout << CLEAR_SCREEN;
	return 0;
}
