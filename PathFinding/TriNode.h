#pragma once
#include "TerrainMap.h"

class TriNode
{
public:
	TriNode();
	TriNode(const int x, const int y, const int up, const int down, const int left, const int right, TerrainMap* tm);
	~TriNode();

	inline int getCost(){
		return terrainMap->getCost(x, y);
	}

private:

	int x;
	int y;

	int up;
	int down;
	int left;
	int right;

	TerrainMap* terrainMap;
};

