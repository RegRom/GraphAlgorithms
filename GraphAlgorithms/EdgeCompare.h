#pragma once
#include "Edge.h"

class EdgeCompare
{
public:
	EdgeCompare();
	~EdgeCompare();
	bool operator() (std::shared_ptr<Edge> p1, std::shared_ptr<Edge> p2);
};

