#include "Map.h"

int main(int argc, char* args[])
{
	Map map;
	map.draw();

	char c;
	std::cin >> c;

	std::cout << CLEAR_SCREEN;
	return 0;
}
