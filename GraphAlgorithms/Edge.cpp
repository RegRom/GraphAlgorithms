#include "stdafx.h"
#include "Edge.h"


Edge::Edge()
{
}

Edge::Edge(int _beginVertex, int _endVertex, int _weight)
{
	this->beginVertex = _beginVertex;
	this->endVertex = _endVertex;
	this->weight = _weight;
}


Edge::~Edge()
{
}

bool Edge::operator<(const std::shared_ptr<Edge> b)
{
	return this->weight < b->weight;
}

bool Edge::operator>(const std::shared_ptr<Edge> b)
{
	return this->weight > b->weight;;
}
