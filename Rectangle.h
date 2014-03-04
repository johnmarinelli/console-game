#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
	int mX, mY, mWidth, mHeight;
	
	Rectangle() : mX(1), mY(1), mWidth(0), mHeight(0)
	{
	}
	
	Rectangle(int x, int y, int width, int height) 
		: mX(x), mY(y), mWidth(width), mHeight(height)
	{
	}
};

#endif
