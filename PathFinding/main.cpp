#pragma once
#include "TerrainMap.h"
#include "TriNode.h"
#include "TriGrid.h"
#include <iostream>

int main(){

	const int YLENGTH = 8;
	const int XLENGTH = 21;

	TriGrid grid;
	grid.FindShortestPath('a', 0, 'u', 7);
	std::string filename = "";
	bool exit = false;
	int command;
	
	while (!exit){
		std::cout << "What would you like to do? " << std::endl;
		std::cout << "1: Run A*\n2: Edit Node\n3: Print Terrain Map\n4: Load New Map\n5: Print Costings\n6: Print ID Map\nAnything Else: Quit" << std::endl;
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
		case 4:
			char contin;

			std::cout << "\nMaps should be located in the TerrainMaps Folder\nThe format can be seen in the TerrainMaps/defaultmap.txt file" << std::endl;
			std::cout << "Would you like to continue (y/n)" << std::endl;
			std::cin >> contin;
			if (tolower(contin) == 'y'){
				std::cout << "Enter file name (excluding folder)" << std::endl;
				std::cin >> filename;
				grid.loadNewTerrainMap("TerrainMaps/" + filename);
			}
			break;
		case 5:
			std::cout << ("(R)oad -     Cost = 1\n(L)ake -     Cost = 1\n(H)ill -     Cost = 2\n(F)orest -   Cost = 3\n(M)ountain - Cost = Cannot Pass") << std::endl;
			break;
		case 6:
			std::cout << "  | a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u" << std::endl;
			std::cout << "1 | 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20" << std::endl;
			std::cout << "2 | 21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41" << std::endl;
			std::cout << "3 | 42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59  60  61  62" << std::endl;
			std::cout << "4 | 63  64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83" << std::endl;
			std::cout << "5 | 84  85  86  87  88  89  90  91  92  93  94  95  96  97  98  99  100 101 102 103 104" << std::endl;
			std::cout << "6 | 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125" << std::endl;
			std::cout << "7 | 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146" << std::endl;
			std::cout << "8 | 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167" << std::endl;

			break;
		default:
			exit = true;
			break;
		}
		std::cout << "\n\n";
	}
	return 0;
}
