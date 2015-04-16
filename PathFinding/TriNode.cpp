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
	this->boolDivergesFrom = false;
	this->boolDivergesTo = false;
}


TriNode::~TriNode(){
}

void TriNode::setG(int g){
	this->g = g;
}

void TriNode::setH(int goalX, int goalY){
	//this->h = abs(goalX - this->x) + abs(goalY - this->y); // Manhat
	
	int x1 = goalX;
	int x2 = this->x;
	int y1 = goalY;
	int y2 = this->y;

	if (goalX > this->x){
		x1 = this->x;
		x2 = goalX;
	}
	if (goalY > this->y){
		y1 = this->y;
		y2 = goalY;
	}

	int xDistance = x2 - x1;
	int yDistance = y2 - y1;

	if (xDistance >= yDistance){
		this->h = xDistance + yDistance; // Manhat
	}
	else { 
		if (((x1 + y1) % 2 == 0) && ((x2 + y2) % 2 == 1)){
			this->h = (2 * yDistance) - 1;
		}
		else if (((x1 + y1) % 2 == 1) && ((x2 + y2) % 2 == 0)){
			this->h = (2 * yDistance) + 1;
		}
		else{
			this->h = 2 * yDistance;
		}
	}
}

void TriNode::calculateF(){
	this->f = this->g + this->h;
}

void TriNode::setParent(TriNode* p){
	this->parent = p;
	this->hasAParent = true;
}

void TriNode::setNeighbours(TriNode nodes[][8]){

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

void TriNode::setDivergeToNode(TriNode* p){
	divergesTo = p;
	boolDivergesTo = true;
}

void TriNode::setDivergeFromNode(TriNode* p){
	divergesFrom = p;
	boolDivergesFrom = true;
}

void TriNode::removeDivergeToNode(){
	divergesTo = nullptr;
	boolDivergesTo = false;
}

void TriNode::removeDivergeFromNode(){
	divergesFrom = nullptr;
	boolDivergesFrom = false;
}

void TriNode::reset(){
	this->hasAParent = false;
	this->boolDivergesFrom = false;
	this->boolDivergesTo = false;
	this->parent = nullptr;
	this->divergesFrom = nullptr;
	this->divergesTo = nullptr;
	this->h = 0;
	this->g = 0;
	this->f = 0;
}

std::ostream& operator<<(std::ostream& outStream, const TriNode* node){
	outStream << node->getId() << " - (" << ((char)(node->getX() + 97)) << ", " << (node->getY() + 1) << ")Cost : " << node->getG();
	return outStream;
}