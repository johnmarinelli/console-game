#ifndef ENTITY_H
#define ENTITY_H

#include "Rectangle.h"

class Entity
{
private:
public:
	Rectangle mRect;
	Entity() : mRect() {};

	virtual void paint() = 0;

	void setRect(const int x, const int y, const int width, const int height)
	{
		mRect.mX = x;
		mRect.mY = y;	
		mRect.mWidth = width;	
		mRect.mHeight = height;
	}
};

#endif
