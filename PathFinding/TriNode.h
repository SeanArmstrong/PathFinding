#pragma once
#include "TerrainMap.h"
#include <vector>
#include <string>
#include <iostream>

class TriNode
{
public:
	TriNode();
	TriNode(const int x, const int y, const int up, const int down, const int left, const int right, TerrainMap* tm);
	~TriNode();

	// Gets cost of the current node
	inline int getCost(){
		return terrainMap->getCost(x, y);
	}

	// Gets the terrain type of the current node
	inline int getType(){
		return terrainMap->getType(x, y);
	}

	// Sets neighbours of the current node using boolean flags and position
	void setNeighbours(TriNode nodes[][8]);

	// Getter Methods
	inline int getX() const { return x; }
	inline int getY() const { return y; }
	inline int getG() const { return g; }
	inline int getH() const { return h; }
	inline int getF() const { return f; }
	inline int getId() const { return id; }

	// Parent Methods
	inline bool hasParent() const { return hasAParent; }
	inline TriNode* getParent() const { return parent; }

	// Get vector of neighbours related to this node
	inline std::vector<TriNode*> getNeighbours() const { return connectedObjects; }

	// Setters
	void setG(int g);
	void setH(int goalX, int goalY);

	// Calculate F based on G and H
	void calculateF();

	void setParent(TriNode* p);

	// Diverging Methods
	inline bool doesDivergeTo() const { return boolDivergesTo; }
	inline bool doesDivergeFrom() const { return boolDivergesFrom; }
	inline TriNode* getDivergeToNode() const { return divergesTo; }
	inline TriNode* getDivergeFromNode() const { return divergesFrom; }

	void setDivergeToNode(TriNode* p);
	void setDivergeFromNode(TriNode* p);

	void removeDivergeToNode();
	void removeDivergeFromNode();

	// Resets F,G,H, Parents and Diverge
	void reset();

private:
	// Unique Id counter
	static int ID;

	//Id for this node
	int id;

	// Neighbours
	int connectedIds[4];
	std::vector<TriNode*> connectedObjects;

	// Position
	int x;
	int y;

	// Has neighbour 1 = true 0 = false
	int up;
	int down;
	int left;
	int right;

	// up + down + left + right
	int numberOfConnectedNodes;

	TerrainMap* terrainMap;

	int g; // cost taken to reach node
	int h; // best guess min to goal - manhatten
	int f;

	TriNode* parent;
	bool hasAParent;

	TriNode* divergesFrom;
	bool boolDivergesFrom;

	TriNode* divergesTo;
	bool boolDivergesTo;
};

std::ostream& operator<<(std::ostream& outStream, const TriNode* node);
