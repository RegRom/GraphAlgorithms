#include "stdafx.h"
#include "NeighboursList.h"

NeighboursList::NeighboursList()
{
}

NeighboursList::NeighboursList(int _size, float _density, bool _directed)
{
	this->density = _density;
	this->size = _size;								//rozmiar o jeden wiêkszy od okreœlonego, gdy¿ w ostatnim wierszu bêd¹ wagi
	this->directed = _directed;
	this->edgeNum = (density * (size) * (size - 1)) / 2;
	for (int i = 0; i < size; i++)
	{
		std::list<std::shared_ptr<Edge> > list;
		graph.push_back(list);
	}
}

NeighboursList::NeighboursList(int _size, bool _directed, int edges)
{
	this->edgeNum = edges;
	this->size = _size;								//rozmiar o jeden wiêkszy od okreœlonego, gdy¿ w ostatnim wierszu bêd¹ wagi
	this->directed = _directed;
	this->density = 2 * edges / (_size*(_size - 1));
	for (int i = 0; i < size; i++)
	{
		std::list<std::shared_ptr<Edge> > list;
		graph.push_back(list);
	}
}


NeighboursList::~NeighboursList()
{
}

void NeighboursList::addEdge(int begin, int end, int weight)
{
	std::shared_ptr<Edge> edge(new Edge(end, weight));
	graph[begin].push_front(edge);

	if (directed)
	{
		std::shared_ptr<Edge> reverse_edge(new Edge(begin, weight));
		graph[end].push_front(reverse_edge);
	}
}
