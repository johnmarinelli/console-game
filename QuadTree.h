#ifndef QUADTREE_H
#define QUADTREE_H

#include "Entity.h"
#include "Rectangle.h"
#include <vector>
#include <algorithm>


/*
* UNCOPYABLE
*/

class QuadTree
{
private:
	enum Nodes { NE = 0, NW = 1, SW = 2, SE = 3, };
	
	const int MAX_OBJECTS = 5; 	//max # of objects before quadtree splits
	const int MAX_DIVISIONS = 4; 
	const int MAX_LEVELS = 3; 	//deepest level subnode

	int mLevel;			//current node level

	std::vector<Entity*> mObjects;  //objects in this quadtree

	const Rectangle mBounds;	//2D space this node occupies
	std::vector<QuadTree*> mNodes;  //subnodes
	
	void split()			//splits this quadtree into 4
	{
		int subnodeWidth = mBounds.mWidth / 2;
		int subnodeHeight = mBounds.mHeight / 2;
		int x = mBounds.mX;
		int y = mBounds.mY;

		mNodes.push_back(new QuadTree(mLevel + 1, Rectangle(x + subnodeWidth, y, subnodeWidth, subnodeHeight)));

		mNodes.push_back(new QuadTree(mLevel + 1, Rectangle(x, y, subnodeWidth, subnodeHeight)));

		mNodes.push_back(new QuadTree(mLevel + 1, Rectangle(x, y + subnodeHeight, subnodeWidth, subnodeHeight)));
		
		mNodes.push_back(new QuadTree(mLevel + 1, Rectangle(x + subnodeWidth, y + subnodeHeight, subnodeWidth, subnodeHeight)));
	}

	/*
	* determine which node rect belongs to. -1 means object isn't completely in
	* a child node and is part of parent node
	*/ 
	int getIndex(Rectangle rect)		
	{	
		int index = -1;
		int verticalMid = mBounds.mX + (mBounds.mWidth / 2);
		int horizontalMid = mBounds.mY + (mBounds.mHeight / 2);

		//object can completely fit in the top quadrants
		bool topquad = (rect.mY < horizontalMid && rect.mY + rect.mHeight < horizontalMid);
		//object can completely fit in bottom quadrants
		bool bottomquad = (rect.mY > horizontalMid);
		
		if(rect.mX < verticalMid && rect.mX + rect.mWidth < verticalMid){
			if(topquad){
				index = Nodes::NW;
			}			
			else if(bottomquad){
				index = Nodes::SW;
			}
		}
	
		else if(rect.mX > verticalMid){
			if(topquad){
				index = Nodes::NE;
			}
			else if(bottomquad){
				index = Nodes::SE;
			}
		}

		return index;
	}

	QuadTree(const QuadTree& c) { }
	QuadTree& operator=(const QuadTree& c) { return *this; }

public:

	QuadTree(int level, Rectangle bounds) : mLevel(level), mBounds(bounds)
	{	
		mObjects.reserve(5);
		mNodes.reserve(4);
	}

	void getObjects(std::vector<Entity*>& rtnObjs, const Rectangle& rect)
	{
		int index = getIndex(rect);

		//if belongs in a smaller box and mNodes has been split
		if(index != -1 && !mNodes.empty()){
			mNodes[index]->getObjects(rtnObjs, rect);
		}
	
		rtnObjs.insert(rtnObjs.end(), mObjects.begin(), mObjects.end());
	}

	void clear()
	{
		mObjects.erase(std::begin(mObjects), std::end(mObjects));
		
		//recursively clear child nodes
		for(int i = 0; i < MAX_DIVISIONS; i++){
			if(mNodes[i] != NULL){
				mNodes[i]->clear();
				mNodes[i] = nullptr;
			}
		}
	}	

	void insert(Entity* obj)
	{
		Rectangle rect = obj->mRect;

		//if this quadtree has been split
		if(!mNodes.empty()){
			int index = getIndex(rect); //get index the obj should be in
			
			if(index != -1){
				mNodes[index]->insert(obj);
			}
		
			return;
		}

		mObjects.push_back(obj);
		
		//if it's time to split this quadtree
		if((mObjects.size() > MAX_OBJECTS) && (mLevel < MAX_LEVELS)){
		
			//is this a leaf trie?
			if(mNodes[0] == NULL){
				split();
			}

			int i = 0;
			while(i < mObjects.size()){
				int index = getIndex(mObjects[i]->mRect);
				if(index != -1){
					mNodes[index]->insert(mObjects[i]);
					mObjects.erase(mObjects.begin() + i);	
				}

				else{
					i++;		
				}
			}
		}
	}

	void display()
	{
		std::cout << "nodes: " << mNodes.size() << std::endl;
		std::cout << "objects " << mObjects.size();
	}
};

#endif
