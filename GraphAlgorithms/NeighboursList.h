#pragma once
#include "Edge.h"
#include "EdgeCompare.h"

class NeighboursList
{
	friend class IncidenceMatrix;
private:
	std::vector< std::list< std::shared_ptr<Edge> > > graph;
	int size, edgeNum;
	float density;
	bool directed;
public:
	NeighboursList();
	NeighboursList(int _size, float _density, bool _directed);
	NeighboursList(int _size, bool _directed, int edges);
	~NeighboursList();
	void addEdge(int begin, int end, int weight);
	void fillGraph();
	void randomFillGraph();
	static NeighboursList *readGraphFromFile(std::string fileName, bool direct);
	void display();
	static NeighboursList *primAlgorithm(NeighboursList *inGraph);
	static void dijkstraAlgorithm(NeighboursList *inGraph, int begin, int end);
	int getSize();
};

