#include "Map.h"

int main(int argc, char* args[])
{
	Map map;
	map.draw();

	std::ofstream outfile("map.txt");
	
	if(outfile){
		map.toFile(outfile);
	}

	char c;
	std::cin >> c;

	std::cout << CLEAR_SCREEN;
	return 0;
}
