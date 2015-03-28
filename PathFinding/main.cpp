#pragma once
#include "TerrainMap.h"
#include "TriNode.h"
#include "TriGrid.h"
#include <iostream>

int main(){

	const int YLENGTH = 8;
	const int XLENGTH = 21;

	TriGrid grid;

	bool exit = false;
	int command;
	while (!exit){
		std::cout << "What would you like to do? " << std::endl;
		std::cout << "1: Run A*\n2: Edit Node\n3: Print Terrain Map\nAnything Else: Quit" << std::endl;
		command = 0;
		std::cin >> command;
		switch (command){
		case 1:
			char startX;
			int startY;

			std::cout << "START NODE" << std::endl;
			std::cout << "Please enter a letter between a and u" << std::endl;
			std::cin >> startX;
			std::cout << "Please enter a number between 1 and 8" << std::endl;
			std::cin >> startY;

			if (tolower(startX) > 'u' || tolower(startX) < 'a' || startY < 1 || startY > 8){
				std::cout << "Incorrect stuff" << std::endl;
				break;
			}
			else{
				char goalX;
				int goalY;

				std::cout << "GOAL NODE" << std::endl;
				std::cout << "Please enter a letter between a and u" << std::endl;
				std::cin >> goalX;
				std::cout << "Please enter a number between 1 and 8" << std::endl;
				std::cin >> goalY;

				if (tolower(goalX) > 'u' || tolower(goalX) < 'a' || goalY < 1 || goalY > 8){
					std::cout << "Incorrect stuff" << std::endl;
					break;
				}
				else{
					grid.FindShortestPath(startX, startY - 1, goalX, goalY - 1);
				}
			}
			break;
		case 2:
			char x;
			int y;
			char type;

			std::cout << "Node to Edit: " << std::endl;
			std::cout << "Please enter a letter between a and u" << std::endl;
			std::cin >> x;
			std::cout << "Please enter a number between 1 and 8" << std::endl;
			std::cin >> y;
			std::cout << "Please enter a type by there first letter\n(R)oad - Cost = 1\n(L)ake - Cost = 1\n(H)ill - Cost = 2\n(F)orest - Cost = 3\n(M)ountain - Cost = Cannot Pass" << std::endl;
			std::cin >> type;
			type = toupper(type);
			x = tolower(x);

			if (x > 'u' || x < 'a' || y < 1 || y > 8){
				std::cout << "Incorrect stuff" << std::endl;
				break;
			}
			else if (type != 'R' && type != 'L' && type != 'H' && type != 'F' && type != 'M'){
				std::cout << "Incorrect type" << std::endl;
				break;
			}
			else{
				grid.changeNodeType(x, y - 1, toupper(type));
				std::cout << "\nUpdated Terrain Map\n" << std::endl;
				grid.printTerrainMap();
				break;
			}
		case 3:
			std::cout << "\nTerrain Map\n" << std::endl;
			grid.printTerrainMap();
			break;
		default:
			exit = true;
			break;
		}
		std::cout << "\n\n";
	}
	return 0;
}
