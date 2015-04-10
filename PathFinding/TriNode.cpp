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
	//this->h = abs(this->x - goalX) + abs(this->y + goalY);
	
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
		//Manhattan
		this->h = xDistance + yDistance;
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


/*
void TriNode::setH(int goalX, int goalY){
int xDistance = abs(this->x - goalX);
int yDistance = abs(this->y - goalY);
if (xDistance >= yDistance){
//Manhattan or Zero is goal node
this->h = xDistance + yDistance;
}
else { //+ - up down logic may be wrong check boolean
if (this->y < goalY){ // goal node is above
if (this->up == 0){ // Can't traverse immediately up
if (yDistance % 2 == 0){ //yDistance is even
this->h = 2 * y;
}
else{ //yDistance is odd
this->h = (2 * y) + 1;
}
}
else{
if (yDistance % 2 == 0){ // yDistance is even
this->h = (2 * y) + 1;
}
else{
this->h = 2 * y; //yDistance is odd
}
}
}
else{ // goal node is below
if (this->down == 0){ // Can't traverse immediately down
if (yDistance % 2 == 0){ // yDistance is even
this->h = 2 * y;
}
else{ // yDistance is odd
this->h = (2 * y) + 1;
}
}
else{ // Can traverse immediately down
if (yDistance % 2 == 0){ // yDistance is even
this->h = (2 * y) + 1;
}
else{ // yDistance is odd
this->h = 2 * y;
}
}
}
}
}*/