#pragma once
#include "Edge.h"
#include "EdgeCompare.h"
#include "NeighboursList.h"

class IncidenceMatrix
{
private:
	std::vector< std::vector<int> > graph;
	int size, edgeNum;
	float density;
	bool directed;
public:
	IncidenceMatrix();
	IncidenceMatrix(int _size, float _density, bool _directed);
	IncidenceMatrix(int _size, bool _directed, int edges);
	~IncidenceMatrix();
	void addEdge(int begin, int end, int i, int weight);
	void fillGraph();
	void randomFillGraph();
	static IncidenceMatrix *readGraphFromFile(std::string fileName, bool direct);
	void display();
	static NeighboursList *primAlgorithm(IncidenceMatrix *inGraph);
	static void dijkstraAlgorithm(IncidenceMatrix *inGraph, int begin, int end);
};

