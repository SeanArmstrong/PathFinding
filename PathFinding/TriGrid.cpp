#include "TriGrid.h"


TriGrid::TriGrid(){
	terrainMap = new TerrainMap;
	generateGrid();
	for (int y = 0; y < YLENGTH; y++){
		for (int x = 0; x < XLENGTH; x++){
			nodes[x][y].setNeighbours(nodes, 21, 8);
		}
	}
	std::cout << nodes[0][0].getCost() << std::endl;
	FindShortestPath('a', 0, 'e', 0);
}


TriGrid::~TriGrid()
{
	delete terrainMap;
}


void TriGrid::FindShortestPath(char startNodeXLetter, int startNodeY, char goalNodeXLetter, int goalNodeY){
	TriNode* startNode = nullptr;
	TriNode* goalNode = nullptr;

	int startNodeX = (int)tolower(startNodeXLetter - 97);
	int goalNodeX = (int)tolower(goalNodeXLetter - 97);

	for (int y = 0; y < YLENGTH; y++){
		for (int x = 0; x < XLENGTH; x++){
			if (nodes[x][y].getX() == startNodeX && nodes[x][y].getY() == startNodeY){
				startNode = &(nodes[x][y]);
			}
			else if (nodes[x][y].getX() == goalNodeX && nodes[x][y].getY() == goalNodeY){
				goalNode = &(nodes[x][y]);
			}
		}
	}

	if (startNode && goalNode && startNode != goalNode){
		startNode->setG(0);
		startNode->setH(goalNodeX, goalNodeY);
		startNode->calculateF();
		openList.insert(startNode);
		TriNode* currentNode = startNode;

		while (currentNode != goalNode || openList.size == 0){
			
			for (int i = 0; i < 4; i++){
				TriNode* comparisonNode = currentNode->getNeighbours[i];
				if (comparisonNode){
					comparisonNode->setG(currentNode->getG() + comparisonNode->getCost());
					comparisonNode->setH(goalNodeX, goalNodeY);
					comparisonNode->calculateF();
					// got to 6C need to add parent to TriNode and check lists using contains perhaps?
				}
			}

			currentNode = *(openList.begin);
		}

		if (openList.size > 0){

		}
		else{
			std::cout << "not Path found";
		}
	}


}


void TriGrid::generateGrid(){
	// This should work for any grid assuming it starts with a upsidedown triangle
	// Terrain map would have to be sync
	int up, down, left, right;
	for (int y = 0; y < YLENGTH; y++){
		for (int x = 0; x < XLENGTH; x++){

			up = down = left = right = 1;

			if (x == 0){ // left element
				left = 0;
			}

			if (x == 20){ // right element
				right = 0;
			}

			if (y % 2 == 0){ //if row is even
				if (x % 2 == 1){
					// odds have downs
					up = 0;
					down = 1;
				}
				if (x % 2 == 0){
					// evens have ups
					up = 1;
					down = 0;
				}
			}
			else{ // row is odd
				if (x % 2 == 1){
					// odds have ups
					up = 1;
					down = 0;
				}
				if (x % 2 == 0){
					// evens have downs
					up = 0;
					down = 1;
				}
			}

			if (y == 0){ // top row
				up = 0;
			}
			else if (y == 7){ // bottom row
				down = 0;
			}

			nodes[x][y] = TriNode(x, y, up, down, left, right, terrainMap);
			std::cout << x << " " << y << " " << up << " " << down << " " << left << " " << right << std::endl;

		}
		std::cout << std::endl;
	}
}
