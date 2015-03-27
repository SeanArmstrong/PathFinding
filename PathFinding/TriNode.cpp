#include "TriNode.h"


TriNode::TriNode(){

}

TriNode::TriNode(const int x, const int y, const int up, const int down, const int left, const int right, TerrainMap* tm){
	this->x = x;
	this->y = y;
	this->up = up;
	this->down = down;;
	this->left = left;
	this->right = right;
	this->terrainMap = tm;
}


TriNode::~TriNode()
{
}
