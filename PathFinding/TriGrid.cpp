#include "TriGrid.h"


TriGrid::TriGrid(){
	terrainMap = new TerrainMap;
	generateGrid();

	std::cout << nodes[0][0].getCost() << std::endl;
}


TriGrid::~TriGrid()
{
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
