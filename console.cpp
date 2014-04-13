#include "Game.h"
#include <unistd.h>

int main()
{
	//call map generating program
	chdir("map-gen");
	int success = system("./mg");
	chdir("../");	
	/*lol fix this*/
	while(success == 35584) {
		success = system("./map-gen/mg");
//		printf("map gen failed: %d\n", success);
//		return 0;
	}

	Game game;
	game.update();
	std::cout << MOVE_TO_0_0;

	return 0;
}
