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
	this->hasADivergeParent = false;
}


TriNode::~TriNode(){
}

void TriNode::setG(int g){
	this->g = g;
}

void TriNode::setH(int goalX, int goalY){
	this->h = abs(this->x - goalX) + abs(this->y - goalY);
	//std::cout << "this.x - goalX  + this.y + goalY = " << this->x << " - " << goalX << " + " << this->y << " "
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

	if (up == 1){
		connectedObjects.push_back(&(nodes[this->x][this->y - 1]));
	}

	if (down == 1){
		connectedObjects.push_back(&(nodes[this->x][this->y + 1]));
	}

	if (left == 1){
		connectedObjects.push_back(&(nodes[this->x - 1][this->y]));
	}

	if (right == 1){
		connectedObjects.push_back(&(nodes[this->x + 1][this->y]));
	}
}

void TriNode::setDivergeParent(TriNode* p){
	divergeParent = p;
	hasADivergeParent = true;
}
