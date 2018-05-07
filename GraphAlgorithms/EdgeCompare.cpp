#include "stdafx.h"
#include "EdgeCompare.h"


EdgeCompare::EdgeCompare()
{
}


EdgeCompare::~EdgeCompare()
{
}

bool EdgeCompare::operator()(const std::shared_ptr<Edge> p1, const std::shared_ptr<Edge> p2) const
{
	//if (p1->weight > p2->weight) return true;
	//if (p1->weight < p2->weight) return false;

	return p1->weight > p2->weight;
}
