#pragma once
#include "TerrainMap.h"
#include "TriNode.h"
#include "TriGrid.h"
#include <iostream>

int main(){

	const int YLENGTH = 8;
	const int XLENGTH = 21;

	TriGrid grid;

	grid.FindShortestPath('a', 1, 'e', 5);

	char exit;
	std::cin >> exit;
	return 0;
}