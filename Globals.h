#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

const int WIDTH = 50;
const int HEIGHT = 10;

const std::string MOVE_TO_0_0 = "\033[1;1f";
const std::string CLEAR_SCREEN = "\033[2J";
const std::string CLEAR_LINE = "\033[K";

const void moveTo(int x, int y)
{
	std::cout << MOVE_TO_0_0;
	printf("\033[%d;%df", y, x);
}

const void moveToInputArea()
{
	moveTo(0, HEIGHT + 4);
}

bool checkCollision(const Entity& a, const Entity& b)
{
	int aLeft = a.mRect.mX;
	int aTop = a.mRect.mY;
	int aRight = aLeft + a.mRect.mWidth;
	int aBottom = aTop + a.mRect.mHeight;

	int bLeft = b.mRect.mX;
	int bTop = b.mRect.mY;
	int bRight = bLeft + b.mRect.mWidth;
	int bBottom = bTop + b.mRect.mHeight;


	if (aLeft >= bRight) return false;
	if (aRight <= bLeft) return false;
	if (aBottom <= bTop) return false;
	if (aTop >= bBottom) return false;
	
	return true; 
}

#endif
