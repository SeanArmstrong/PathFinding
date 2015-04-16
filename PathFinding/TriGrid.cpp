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
	for (int y = 0; y < YLENGTH; y++){
		for (int x = 0; x < XLENGTH; x++){
			nodes[x][y].reset();
		}
	}
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

void TriGrid::AStar(TriNode* startNode, TriNode* goalNode){
	// Useful variables
	int goalNodeX = goalNode->getX();
	int goalNodeY = goalNode->getY();
	bool pathFound = false;

	// Setup start node
	startNode->setG(0);
	startNode->setH(goalNodeX, goalNodeY);
	startNode->calculateF();
	openList.insert(startNode);

	TriNode* currentNode = startNode;

	// Iterators for lists
	std::multiset<TriNode*>::iterator openListIt;
	std::list<TriNode*>::iterator closedListIt;

	while (openList.size() > 0){
		//printOpenList();
		currentNode = *(openList.begin()); // Set current node to lowest f

		openList.erase(openList.begin()); // Pop from openlist
		closedList.push_front(currentNode);

		if (currentNode == goalNode){
			pathFound = true;
			break; // Break if path found (best first)
		}

		std::vector<TriNode*> neighbours = currentNode->getNeighbours();
		for (int i = 0; i < neighbours.size(); i++){
			int newGValue = 0;
			TriNode* comparisonNode = neighbours[i];
			TriNode* divergingNode = nullptr;

			if (comparisonNode){
				if (comparisonNode->getCost() < 0){ // we have a mountain to climb
					continue;
				}

				newGValue = currentNode->getG() + comparisonNode->getCost();

				/*** Multiple Lakes ***/
				if ((comparisonNode->getType() == 'L'&& currentNode->getType() == 'L' &&  // Comp and Curren Node are lakes
					(currentNode->hasParent() && currentNode->getParent()->getType() == 'L')) && // current node parent is lake
					comparisonNode != currentNode->getParent()){ // Not backtracking

					// Find another neighbour which is not a lake or a mountain
					divergingNode = findLowestCostNeighbour(currentNode, comparisonNode);
					if (!divergingNode){ // can't find appropriate neighbour
						continue; // No route to diverge to
					}
					newGValue += divergingNode->getCost() + currentNode->getCost(); // Increase new g value to count diverge
				}

				// compNode H value
				comparisonNode->setH(goalNodeX, goalNodeY);

				openListIt = openList.find(comparisonNode);
				closedListIt = std::find(closedList.begin(), closedList.end(), comparisonNode);
				if (openListIt != openList.end() || closedListIt != closedList.end()){ // on the open or closed list
					if (newGValue <= comparisonNode->getG()){
						if (openListIt != openList.end()){
							openListIt = openList.erase(openListIt);
							UpdateNodes(comparisonNode, currentNode, newGValue, divergingNode);
							openListIt = openList.insert(openListIt, comparisonNode);
						}
						else{
							UpdateNodes(comparisonNode, currentNode, newGValue, divergingNode);
						}		
					}
				}
				else{ // First path on node
					UpdateNodes(comparisonNode, currentNode, newGValue, divergingNode);
					openList.insert(comparisonNode);
				}
			}
		}
	}

	if (pathFound == true){
		printPath(closedList.front());
	}
}

void TriGrid::UpdateNodes(TriNode* comparisonNode, TriNode* currentNode, int g, TriNode* divergingNode){
	comparisonNode->setG(g);
	comparisonNode->calculateF();
	comparisonNode->setParent(currentNode);
	if (divergingNode){
		SetDivergeForNodes(currentNode, divergingNode);
	}

}
void TriGrid::SetDivergeForNodes(TriNode* currentNode, TriNode* divergingNode){
	currentNode->setDivergeToNode(divergingNode);
	divergingNode->setG(currentNode->getG() + divergingNode->getCost());
	divergingNode->calculateF();
	divergingNode->setDivergeFromNode(currentNode);
}

TriNode* TriGrid::findLowestCostNeighbour(TriNode* currentNode, TriNode* comparisonNode){
	std::vector<TriNode*> diversionNeighbours = currentNode->getNeighbours();
	TriNode* divergingNode = nullptr;
	int lowestCost = 10;

	// Find lowest cost neighbour
	for (int d = 0; d < diversionNeighbours.size(); d++){
		if (diversionNeighbours[d] != currentNode->getParent() && diversionNeighbours[d] != comparisonNode){
			if (diversionNeighbours[d]->getType() != 'L' && diversionNeighbours[d]->getType() != 'M' && 
				diversionNeighbours[d]->getCost() < lowestCost){ 
				divergingNode = diversionNeighbours[d];
				lowestCost = diversionNeighbours[d]->getCost();
			}
		}
	}
	return divergingNode;
}

void TriGrid::printPath(const TriNode* printingNode) const {
	std::cout << "Path: " << std::endl;
	std::cout << "H Value" << printingNode->getH() << std::endl;
	std::cout << "Cost: " << printingNode->getG() << std::endl;
	std::cout << "Goal Node: " << printingNode << std::endl;

	while (printingNode->hasParent()){
		printingNode = printingNode->getParent();

		if (!printingNode->hasParent())
			break;
		
		if (printingNode->doesDivergeTo() && printingNode->getDivergeToNode()->getDivergeFromNode() == printingNode){
			std::cout << "Next Node: " << printingNode << " - Diverges via: " << printingNode->getDivergeToNode() << std::endl;
		}
		else{
			std::cout << "Next Node: " << printingNode << std::endl;
		}
	}
	std::cout << "Start Node: " << printingNode << std::endl;
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
		}
	}
}

