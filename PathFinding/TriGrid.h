#pragma once
#include "TriNode.h"
#include "TerrainMap.h"
#include <iostream>
#include <set>
#include <list>

class TriGrid
{
public:
	TriGrid();
	~TriGrid();

	void FindShortestPath(char startNodeXLetter, int startNodeY, char goalNodeXLetter, int goalNodeY);

	void changeNodeType(const char x, const int y, const char type);
	void printTerrainMap();
	void loadNewTerrainMap(const std::string filename);


	TriNode nodes[21][8];

private:
	
	void AStar(TriNode* startNode, TriNode* goalNode);

	// If node is a lake
	// and current node is a lake
	// and current node parent is a lake
	// Then it would be on its third. So 
	// Need to go to cheapest near node, back to current node
	// then to neighbour and set path if this is the cheapest
	void multipleLakes(TriNode* currentNode, TriNode* comparisonNode, const int goalNodeX, const int goalNodeY);
	
	void printPath(const TriNode* printingNode) const;
	
	void generateGrid();

	const int XLENGTH = 21;
	const int YLENGTH = 8;


	TerrainMap* terrainMap;

	std::multiset<TriNode*> openList;
	std::list<TriNode*> closedList;
};

