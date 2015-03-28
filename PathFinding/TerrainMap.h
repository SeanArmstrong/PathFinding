#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <map>

class TerrainMap
{
public:

	TerrainMap();
	TerrainMap(std::string filename);
	~TerrainMap();

	// Print the terrain map
	void printMap() const;

	// Update the value of a given triangle
	void updateValue(const char x, const int y, const char newValue);

	//
	void loadNewMap(const std::string filename);

	// Get cost of given triangle
	int getCost(const char x, const int y);
	int getCost(const int x, const int y);

	// Access a value using a letter and a number
	char operator()(const char x, const int y) const;

private: 

	const int XLENGTH = 21;
	const int YLENGTH = 8;

	void terrainFromFile(const std::string filename = "TerrainMaps/defaultmap.txt");
	void setCostings();
		
	char map[21][8];

	char R = 'R'; // Road
	char L = 'L'; // Lake
	char F = 'F'; // Forest cost = 3
	char H = 'H'; // Hill cost = 2
	char M = 'M'; // Mountain you shall not passs

	std::map<char, int> costing;

};

