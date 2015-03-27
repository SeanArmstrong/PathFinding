#pragma once
#include "TriNode.h"
#include "TerrainMap.h"
#include <iostream>
#include <set>

class TriGrid
{
public:
	TriGrid();
	~TriGrid();

	void FindShortestPath(char startNodeXLetter, int startNodeY, char goalNodeXLetter, int goalNodeY);

private:
	
	void generateGrid();

	const int XLENGTH = 21;
	const int YLENGTH = 8;

	TriNode nodes[21][8];

	TerrainMap* terrainMap;

	std::multiset<TriNode*> openList;
	std::multiset<TriNode*> closedList;
};

