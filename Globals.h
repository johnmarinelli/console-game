#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <queue>
#include <iostream>
#include <string>

#include <unistd.h>

const int WIDTH = 100;
const int HEIGHT = 10;

const std::string MOVE_TO_0_0 = "\033[1;1f";
const std::string CLEAR_SCREEN = "\033[2J";
const std::string CLEAR_LINE = "\033[K";

std::queue<std::string> globalOutputs;

const void moveTo(int x, int y)
{
	std::cout << MOVE_TO_0_0;
	printf("\033[%d;%df", y, x);
}

const void moveToInputArea()
{
	moveTo(0, HEIGHT + 4);
}

const bool runMapGenerator()
{
	chdir("map-gen");
	bool success = system("./mg");
	chdir("../");

	return success;
}

#endif
