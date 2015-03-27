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
}


TriNode::~TriNode()
{
}

void TriNode::setG(int g){
	this->g = g;
}

void TriNode::setH(int goalX, int goalY){
	abs(this->x - goalX) + abs(this->y + goalY);
}

void TriNode::calculateF(){
	f = g + h;
}

bool TriNode::operator<(const TriNode rhs){
	return (this->f < rhs.f);
}

void TriNode::setNeighbours(TriNode nodes[][8], const int xsize, const int ysize){
	// This could be MUCH more Efficent but will do for now.
	// This code disgust me and i wrote it
	if (up == 1){
		for (int y = 0; y < ysize; y++){
			for (int x = 0; x < xsize; x++){
				if ((nodes[x][y].y == (this->y + 1)) && (nodes[x][y].x == this->x)){
					connectedIds[0] = nodes[x][y].id;
					connectedObjects[0] = &(nodes[x][y]);
					break;
				}
			}
		}
	}

	if (down == 1){
		for (int y = 0; y < ysize; y++){
			for (int x = 0; x < xsize; x++){
				if ((nodes[x][y].y == (this->y - 1)) && (nodes[x][y].x == this->x)){
					connectedIds[1] = nodes[x][y].id;
					connectedObjects[1] = &(nodes[x][y]);
					break;
				}
			}
		}
	}

	if (left == 1){
		for (int y = 0; y < ysize; y++){
			for (int x = 0; x < xsize; x++){
				if ((nodes[x][y].x == (this->x - 1)) && (nodes[x][y].y == this->y)){
					connectedIds[2] = nodes[x][y].id;
					connectedObjects[2] = &(nodes[x][y]);
					break;
				}
			}
		}
	}

	if (right = 1){
		for (int y = 0; y < ysize; y++){
			for (int x = 0; x < xsize; x++){
				if ((nodes[x][y].x == (this->x + 1)) && (nodes[x][y].y == this->y)){
					connectedIds[3] = nodes[x][y].id;
					connectedObjects[3] = &(nodes[x][y]);
					break;
				}
			}
		}
	}
}
