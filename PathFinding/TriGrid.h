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


	TriNode nodes[21][8];

private:
	
	void generateGrid();

	const int XLENGTH = 21;
	const int YLENGTH = 8;


	TerrainMap* terrainMap;

	std::multiset<TriNode*> openList;
	std::list<TriNode*> closedList;
};

