#pragma once
#include "Edge.h"

class NeighboursList
{
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
};

