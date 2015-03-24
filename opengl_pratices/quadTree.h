#include <iostream>
#include <vector>
#include <list>
#ifndef QUADTREE_H
#define QUADTREE_H
typedef struct Rect{

public:	Rect(int x, int y, int width, int height){
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
}
		Rect(){
			this->x = this->y = this->height = this->width = 0;
		}
		int x;
		int y;
		int width;
		int height;
}Rect;

class QuadTree{
public:
	QuadTree(){}
	QuadTree(int level, Rect bounds);
	void split();			//划分
	int getIndex(Rect r);	//得到 0 1 2 3 -1
	void insert(Rect r);	// 插入节点
	const 	int MaxObj = 10;
	const   int MaxLevel = 6;
	int level;
	Rect	bounds;
	std::list<Rect> rectObj;
	std::vector<QuadTree> nodes;
};
#endif
