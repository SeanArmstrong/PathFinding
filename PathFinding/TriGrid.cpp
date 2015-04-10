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

void TriGrid::multipleLakes(TriNode* currentNode, TriNode* comparisonNode, const int goalNodeX, const int goalNodeY){
	std::multiset<TriNode*>::iterator openListIt;
	std::list<TriNode*>::iterator closedListIt;

	std::vector<TriNode*> diversionNeighbours = currentNode->getNeighbours();
	TriNode* divergingNode = nullptr;
	int lowestCost = 10;

	// Find lowest cost neighbour
	for (int d = 0; d < diversionNeighbours.size(); d++){
		if (diversionNeighbours[d] != currentNode->getParent() && diversionNeighbours[d] != comparisonNode){
			if (diversionNeighbours[d]->getCost() < lowestCost){
				divergingNode = diversionNeighbours[d];
				lowestCost = diversionNeighbours[d]->getCost();
			}
		}
	}

	if (divergingNode){
		int newDivergeGValue = currentNode->getG() + divergingNode->getCost();
		int newCurrentNodeGValue = currentNode->getG() + divergingNode->getCost() + currentNode->getCost();
		int newComparisonNodeGValue = newCurrentNodeGValue + comparisonNode->getCost();
		comparisonNode->setH(goalNodeX, goalNodeY);
		openListIt = openList.find(comparisonNode);
		closedListIt = std::find(closedList.begin(), closedList.end(), comparisonNode);
		if (openListIt != openList.end() || closedListIt != closedList.end()){ // on the open or closed list
			if (newComparisonNodeGValue < comparisonNode->getG()){ // new best route
				comparisonNode->setG(newComparisonNodeGValue);
				comparisonNode->calculateF();
				comparisonNode->setParent(currentNode);
				currentNode->setDivergeToNode(divergingNode);
				currentNode->setG(newCurrentNodeGValue);
				divergingNode->setG(newDivergeGValue);
				divergingNode->calculateF();
				divergingNode->setDivergeFromNode(currentNode);
			}
		}
		else{
			comparisonNode->setG(newComparisonNodeGValue);
			comparisonNode->calculateF();
			comparisonNode->setParent(currentNode);
			currentNode->setDivergeToNode(divergingNode);
			currentNode->setG(newCurrentNodeGValue);
			divergingNode->setG(newDivergeGValue);
			divergingNode->calculateF();
			divergingNode->setDivergeFromNode(currentNode);
			openList.insert(comparisonNode);
		}
	}
}

void TriGrid::AStar(TriNode* startNode, TriNode* goalNode){
	int goalNodeX = goalNode->getX();
	int goalNodeY = goalNode->getY();
	for (int y = 0; y < YLENGTH; y++){
		for (int x = 0; x < XLENGTH; x++){
			nodes[x][y].reset();
		}
	}

	bool pathFound = false;
	startNode->setG(0);
	startNode->setH(goalNodeX, goalNodeY);
	startNode->calculateF();
	openList.insert(startNode);
	TriNode* currentNode = startNode;

	std::multiset<TriNode*>::iterator openListIt;
	std::list<TriNode*>::iterator closedListIt;

	while (openList.size() > 0){
		currentNode = *(openList.begin()); // Set current node to lowest f
		std::cout << "Current Node: " << currentNode->getId() << std::endl;

		openList.erase(openList.begin()); // Pop from openlist
		closedList.push_front(currentNode);

		if (currentNode == goalNode){
			pathFound = true;
			closedList.push_front(currentNode);
			break;
		}

		std::vector<TriNode*> neighbours = currentNode->getNeighbours();

		for (int i = 0; i < neighbours.size(); i++){
			std::cout << "Neighbour: " << i << std::endl;

			int newGValue = 0;

			TriNode* comparisonNode = neighbours[i];

			//if (comparisonNode->hasDivergeParent() && comparisonNode->getDivergeParent() == currentNode){
			//	continue;
			//}

			if (comparisonNode){
				if (comparisonNode->getCost() < 0){ // we have a mountain to climb
					continue;
				}

				/*** Multiple Lakes ***/
				if ((terrainMap->getType(comparisonNode->getX(), comparisonNode->getY()) == 'L'&& // Comp node is lake
					terrainMap->getType(currentNode->getX(), currentNode->getY()) == 'L' && // Current node is lake
					(currentNode->hasParent() && terrainMap->getType(currentNode->getParent()->getX(), currentNode->getParent()->getY()) == 'L')) &&
					comparisonNode != currentNode->getParent()){ // parent is lake

					multipleLakes(currentNode, comparisonNode, goalNodeX, goalNodeY);

				}
				else{
					newGValue = currentNode->getG() + comparisonNode->getCost();
					comparisonNode->setH(goalNodeX, goalNodeY);
					comparisonNode->calculateF();

					openListIt = openList.find(comparisonNode);
					closedListIt = std::find(closedList.begin(), closedList.end(), comparisonNode);
					if (openListIt != openList.end() || closedListIt != closedList.end()){ // on the open or closed list
						if (newGValue < comparisonNode->getG()){
							//currentNode->setHasADivergeParent(false);
							//comparisonNode->setHasADivergeParent(false);
							comparisonNode->setG(newGValue);
							comparisonNode->calculateF();
							comparisonNode->setParent(currentNode);
						}
					}
					else{
						//currentNode->setHasADivergeParent(false);
						//comparisonNode->setHasADivergeParent(false);
						comparisonNode->setG(newGValue);
						comparisonNode->calculateF();
						comparisonNode->setParent(currentNode);
						openList.insert(comparisonNode);
					}
				}
			}
		}
	}

	if (pathFound == true){
		printPath(closedList.front());
	}
}

void TriGrid::FindShortestPath(char startNodeXLetter, int startNodeY, char goalNodeXLetter, int goalNodeY){
	openList.clear();
	closedList.clear();


	TriNode* startNode = nullptr;
	TriNode* goalNode = nullptr;

	int startNodeX = (int)tolower(startNodeXLetter - 97);
	int goalNodeX = (int)tolower(goalNodeXLetter - 97);

	startNode = &(nodes[startNodeX][startNodeY]);
	goalNode = &(nodes[goalNodeX][goalNodeY]);

	if (goalNode && startNode){
		if (startNode == goalNode){
			std::cout << "Error: Goal node is same and start node" << std::endl;
		}
		else if (goalNode->getCost() < 0){ // Can you start on one. In theory you are going down. Might be ok?
			std::cout << "Error: Cannot finish on a mountain" << std::endl;
		}
		else{
			AStar(startNode, goalNode);
		}
	}
	else{
		std::cout << "Could not find goal or start node" << std::endl;
	}
}

void TriGrid::printPath(const TriNode* printingNode) const {
	std::cout << "Path: " << std::endl;

	std::cout << "Goal Node: " << printingNode->getId() << " x: " << printingNode->getX() <<
		", y: " << printingNode->getY() << std::endl;

	while (printingNode->hasParent()){
		printingNode = printingNode->getParent();
		
		 // TODO: Tidy up loop and checks
		if (!printingNode->hasParent()){
			break;
		}

		if (printingNode->doesDivergeTo() && printingNode->getDivergeToNode()->getDivergeFromNode() == printingNode){
			// Then it diverges
			std::cout << "Next Node: " << printingNode->getId() << " x: " << printingNode->getX() <<
				", y: " << printingNode->getY() << " - Diverges via: " << printingNode->getDivergeToNode()->getId() << std::endl;
		}
		else{
			std::cout << "Next Node: " << printingNode->getId() << " x: " << printingNode->getX() <<
				", y: " << printingNode->getY() <<  std::endl;
		}
	}

	std::cout << "Start Node: " << printingNode->getId() << " x: " << printingNode->getX() <<
		", y: " << printingNode->getY() << std::endl;



	std::cout << "Path Cost: " << closedList.front()->getF() << std::endl;
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
