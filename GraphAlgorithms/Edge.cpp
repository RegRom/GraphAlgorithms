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
