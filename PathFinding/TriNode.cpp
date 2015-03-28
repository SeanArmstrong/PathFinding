#include "TriNode.h"

int TriNode::ID = 0;

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
	this->id = ID++;
	this->numberOfConnectedNodes = up + down + left + right;
	this->hasAParent = false;
}


TriNode::~TriNode()
{
}

void TriNode::setG(int g){
	this->g = g;
}

void TriNode::setH(int goalX, int goalY){
	this->h = abs(this->x - goalX) + abs(this->y + goalY);
}

void TriNode::calculateF(){
	this->f = this->g + this->h;
}

void TriNode::setParent(TriNode* p){
	this->parent = p;
	this->hasAParent = true;
}

bool TriNode::operator<(const TriNode rhs){
	return (this->f < rhs.f);
}

void TriNode::setNeighbours(TriNode nodes[][8], const int xsize, const int ysize){

	//std::cout << this->id << std::endl;

	if (up == 1){
		//std::cout << "UP" << std::endl;
		connectedObjects.push_back(&(nodes[this->x][this->y - 1]));
	}

	if (down == 1){
		//std::cout << "DOWN" << std::endl;
		std::cout << (nodes[this->x][this->y - 1]).getId() << std::endl;
		connectedObjects.push_back(&(nodes[this->x][this->y + 1]));
	}

	if (left == 1){
		//std::cout << "LEFT" << std::endl;
		connectedObjects.push_back(&(nodes[this->x - 1][this->y]));
	}

	if (right == 1){
		//std::cout << "RIGHT" << std::endl;
		connectedObjects.push_back(&(nodes[this->x + 1][this->y]));
	}
}
