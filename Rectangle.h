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

void drawRect(const Rectangle& rect, const char gfx)
{
   int i = 0, j = 0;

    for(i = 0; i < rect.mHeight; ++i){
       moveTo(rect.mX, rect.mY + i);
       for(j = 0; j < rect.mWidth; ++j){
           printf("%c", gfx);
       }
    }
}


#endif
