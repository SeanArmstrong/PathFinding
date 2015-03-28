#pragma once
#include "TerrainMap.h"
#include <vector>

class TriNode
{
public:
	TriNode();
	TriNode(const int x, const int y, const int up, const int down, const int left, const int right, TerrainMap* tm);
	~TriNode();

	inline int getCost(){
		return terrainMap->getCost(x, y);
	}

	void setNeighbours(TriNode nodes[][8], const int xsize, const int ysize);

	inline int getX() const { return x; }
	inline int getY() const { return y; }
	inline int getG() const { return g; }
	inline int getH() const { return h; }
	inline int getF() const { return f; }
	inline int getId() const { return id; }
	inline bool hasParent() const { return hasAParent; }
	inline TriNode* getParent() const { return parent; }
	//inline TriNode* getNeighbours() const { return *connectedObjects; }
	inline std::vector<TriNode*> getNeighbours() const { return connectedObjects; }

	void setG(int g);
	void setH(int goalX, int goalY);
	void calculateF();

	void setParent(TriNode* p);

	bool operator<(const TriNode rhs);

private:
	static int ID;
	int id;

	int connectedIds[4];
	//TriNode* connectedObjects[4];
	std::vector<TriNode*> connectedObjects;

	int x;
	int y;

	int up;
	int down;
	int left;
	int right;

	int numberOfConnectedNodes;

	TerrainMap* terrainMap;

	int g; // cost taken to reach node
	int h; // best guess min to goal - manhatten
	int f;

	TriNode* parent;
	bool hasAParent;
};

