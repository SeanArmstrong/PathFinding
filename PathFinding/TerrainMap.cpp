#include "TerrainMap.h"


TerrainMap::TerrainMap(){
	terrainFromFile();
	setCostings();
}

TerrainMap::TerrainMap(std::string filename){
	terrainFromFile(filename);
	setCostings();
}


TerrainMap::~TerrainMap()
{
}

void TerrainMap::printMap() const {
	std::cout << "  a b c d e f g h i j k l m n o p q r s t u" << std::endl;
	for (int y = 0; y < YLENGTH; ++y){
		std::cout << y + 1 << " ";
		for (int x = 0; x < XLENGTH; ++x){
			std::cout << map[x][y] << " ";
		}
		std::cout << "\n";
	}
}

void TerrainMap::updateValue(const char x, const int y, const char newValue){
	map[(int) tolower(x) - 97][y] = newValue;
}

void TerrainMap::loadNewMap(const std::string filename){
	terrainFromFile(filename);
}

int TerrainMap::getCost(const char x, const int y){
	return getCost((int)tolower(x) - 97, y);
}

int TerrainMap::getCost(const int x, const int y) {
	char value = map[x][y];
	std::map<char, int>::iterator it = costing.find(value);
	if (it != costing.end()){
		return it->second;
	}
	return 0;
}

char TerrainMap::getType(const int x, const int y) const{
	return map[x][y];
}

char TerrainMap::operator()(const char x, const int y) const {
	std::cout << (int) tolower(x) - 97 << std::endl;
	return map[(int)x - 97][y-1];
}

char TerrainMap::operator()(const int x, const int y) const{
	return map[x][y];
}


void TerrainMap::terrainFromFile(const std::string filename){
	std::ifstream file(filename);
	for (int i = 0; i < 8; i++){
		std::string str;
		std::getline(file, str);
		int step = 0;
		for (std::string::size_type j = 0; j < str.size(); j += 2) {
			map[step][i] = str[j];
			step++;
		}
	}
}

void TerrainMap::setCostings(){
	costing.insert(std::make_pair('R', 1));
	costing.insert(std::make_pair('L', 1));
	costing.insert(std::make_pair('H', 2));
	costing.insert(std::make_pair('F', 3));
	costing.insert(std::make_pair('M', -1));
}