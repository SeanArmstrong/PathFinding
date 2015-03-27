#pragma once
#include "TriNode.h"
#include "TerrainMap.h"
#include <iostream>

class TriGrid
{
public:
	TriGrid();
	~TriGrid();

private:
	
	const int XLENGTH = 21;
	const int YLENGTH = 8;

	TriNode nodes[21][8];

	TerrainMap* terrainMap;


	void generateGrid();
};

