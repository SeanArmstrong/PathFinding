#pragma once
#include "TriNode.h"
#include "TerrainMap.h"
#include <iostream>
#include <set>
#include <list>

class TriGrid
{
public:

	TriGrid();
	~TriGrid();

	// Public method to get shortest path. Uses A* algorithm
	void FindShortestPath(char startNodeXLetter, int startNodeY, char goalNodeXLetter, int goalNodeY);

	// Changes node terrain type to new param(type)
	void changeNodeType(const char x, const int y, const char type);

	// Print terrainMap associated with this Grid
	void printTerrainMap();

	// Loads new terrain map for this grid
	void loadNewTerrainMap(const std::string filename);

	// Array of nodes
	TriNode nodes[21][8];

private:
	// Compartor for openList multiset
	struct compare {
		bool operator()(TriNode* lhs, TriNode* rhs) const {
			return lhs->getF() < rhs->getF();
		}
	};
	
	// A* Algorithm from startNode to goalNode
	void AStar(TriNode* startNode, TriNode* goalNode);

	// Prints path from goal node to start node via parents
	void printPath(const TriNode* printingNode) const;

	// Gets the lowest cost neighbour to the current node that isn' the comparison node
	TriNode* findLowestCostNeighbour(TriNode* currentNode, TriNode* comparisonNode);
	
	// Updates G and F values of nodes, sets parents and applies diverge
	void UpdateNodes(TriNode* comparisonNode, TriNode* currentNode, int g, TriNode* divergingNode = nullptr);
	void SetDivergeForNodes(TriNode* currentNode, TriNode* divergingNode);

	// Generates the triangle grid of nodes
	void generateGrid();
	
	// Helper to print open list to console
	void printOpenList();

	const int XLENGTH = 21;
	const int YLENGTH = 8;

	TerrainMap* terrainMap;

	// OpenList multiset sorts by compare function.
	std::multiset<TriNode*, compare> openList;
	std::list<TriNode*> closedList;
};