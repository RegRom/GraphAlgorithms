#include "stdafx.h"
#include "Edge.h"


Edge::Edge()
{
}

Edge::Edge(int _vertex, int _weight)
{
	this->vertex = _vertex;
	this->weight = _weight;
}


Edge::~Edge()
{
}
