#ifndef GUI_H
#define GUI_H

class Gui
{
public:
	Gui()
	{
	}

	void drawMap(LevelMap& map)
	{
	    std::cout << CLEAR_SCREEN;
	    std::cout << MOVE_TO_0_0;
		
		//make space for stats 
		moveTo(0, 2);
	
	    map.draw();
	}

	void drawGUIBorder()
	{
	    int borderXMargin = WIDTH + 4;
	    std::cout << MOVE_TO_0_0;

	    for(int i = 1; i < HEIGHT + 1; ++i){
	        printf("\033[%d;%df", i, borderXMargin); printf("|");
	    }
	}

	void drawGUI()
	{
	    int borderXMargin = WIDTH + 7;
	    std::cout << MOVE_TO_0_0;

	    printf("\033[%d;%df", 1, borderXMargin); printf("INVENTORY");
	}

	//player is for debug purposes
	void writeOutput(const Statistics& stats, Player player)
	{
	    std::cout << MOVE_TO_0_0;
		std::cout << "Health: " << stats.Health << "	"
				  << "ATK: " << stats.Damage << "		" 
				  << "X, Y: " << player.mRect.mX << ", " << player.mRect.mY << "	";

	    moveTo(0, HEIGHT + 1);
	
	    while(!globalOutputs.empty()){
	        std::cout << globalOutputs.front() << std::endl;
	        globalOutputs.pop();
	    }
	}
	
};

#endif
