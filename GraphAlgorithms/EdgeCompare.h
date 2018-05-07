#pragma once
#include "Edge.h"

class EdgeCompare
{
public:
	EdgeCompare();
	~EdgeCompare();
	bool operator() (const std::shared_ptr<Edge> p1, const std::shared_ptr<Edge> p2) const;
};

