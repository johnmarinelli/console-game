#include "Map.h"

int main(int argc, char* args[])
{
	Map map;
	map.init();

	std::cout << "Generating map...";

	std::ofstream outfile("map.txt");
	std::ofstream infofile("mapinfo.txt");
	
	if(outfile && infofile){
		map.gfxToFile(outfile);
		map.infoToFile(infofile);
	
		std::cout << "done.\n";
	}

	else{
		return 1;
	}

	return 0;
}
