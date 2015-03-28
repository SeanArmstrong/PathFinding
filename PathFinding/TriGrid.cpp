#include "TriGrid.h"


TriGrid::TriGrid(){
	terrainMap = new TerrainMap;
	generateGrid();
	for (int y = 0; y < YLENGTH; y++){
		for (int x = 0; x < XLENGTH; x++){
			nodes[x][y].setNeighbours(nodes, XLENGTH, YLENGTH);
		}
	}
}


TriGrid::~TriGrid()
{
	delete terrainMap;
}

void TriGrid::changeNodeType(const char x, const int y, const char type){
	terrainMap->updateValue(x, y, type);
}

void TriGrid::printTerrainMap(){
	terrainMap->printMap();
}

void TriGrid::loadNewTerrainMap(const std::string filename){
	terrainMap->loadNewMap(filename);
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

	if (goalNode && startNode){
		if (startNode == goalNode){
			std::cout << "Error: Goal node is same and start node" << std::endl;
		}
		else if (goalNode->getCost() < 0){ // Can you start on one. In theory you are going down. Might be ok?
			std::cout << "Error: Cannot finish on a mountain" << std::endl;

		}
		else{
			bool pathFound = false;
			startNode->setG(0);
			startNode->setH(goalNodeX, goalNodeY);
			startNode->calculateF();
			openList.insert(startNode);
			TriNode* currentNode = startNode;

			std::multiset<TriNode*>::iterator openListIt;
			std::list<TriNode*>::iterator closedListIt;

			while (openList.size() > 0){
				std::cout << openList.size() << std::endl;
				currentNode = *(openList.begin()); // Set current node to lowest f
				openList.erase(openList.begin()); // Pop from openlist
				closedList.push_front(currentNode);

				if (currentNode == goalNode){
					pathFound = true;
					closedList.push_front(currentNode);
					break;
				}

				std::vector<TriNode*> neighbours = currentNode->getNeighbours();
				std::cout << "Current Node: " << currentNode->getId() << "- number of neighbours" << neighbours.size() << std::endl;
				for (int i = 0; i < neighbours.size(); i++){
					std::cout << "Current Node: " << currentNode->getId() << "- Neighbour " << i << "  Neighbour ID: " << neighbours[i]->getId() << " Cost: " << neighbours[i]->getCost() << std::endl;
					int newGValue = 0;

					TriNode* comparisonNode = neighbours[i];
					if (comparisonNode){
						if (comparisonNode->getCost() < 0){ // we have a mountain to climb
							std::cout << "Can't climb a mountain" << std::endl;
							continue;
						}

						newGValue = currentNode->getG() + comparisonNode->getCost();
						comparisonNode->setH(goalNodeX, goalNodeY);
						comparisonNode->calculateF();

						openListIt = openList.find(comparisonNode);
						closedListIt = std::find(closedList.begin(), closedList.end(), comparisonNode);
						if (openListIt != openList.end() || closedListIt != closedList.end()){ // on the open or closed list
							if (newGValue < comparisonNode->getG()){
								comparisonNode->setG(newGValue);
								comparisonNode->calculateF();
								comparisonNode->setParent(currentNode);
							}
						}
						else{
							comparisonNode->setG(newGValue);
							comparisonNode->calculateF();
							comparisonNode->setParent(currentNode);
							openList.insert(comparisonNode);
						}
					}
				}
			}

			if (pathFound == true){
				std::cout << "Path: " << std::endl;

				// Print path
				TriNode* printingNode = closedList.front();
				std::cout << "Goal Node: " << printingNode->getId() << " x: " << printingNode->getX() <<
					", y: " << printingNode->getY() << std::endl;

				while (printingNode->hasParent()){
					printingNode = printingNode->getParent();
					std::cout << "Next Node: " << printingNode->getId() << " x: " << printingNode->getX() <<
						", y: " << printingNode->getY() << std::endl;
				}

				std::cout << "Path Cost: " << closedList.front()->getF() << std::endl;
			}
			else{
				std::cout << "Cannot Find Path" << std::endl;
			}
		}
	}
	else{
		std::cout << "Could not find goal or start node" << std::endl;
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
			//std::cout << x << " " << y << " " << up << " " << down << " " << left << " " << right << std::endl;

		}
		//std::cout << std::endl;
	}
}
