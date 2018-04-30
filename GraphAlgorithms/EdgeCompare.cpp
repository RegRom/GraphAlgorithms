#include "stdafx.h"
#include "EdgeCompare.h"


EdgeCompare::EdgeCompare()
{
}


EdgeCompare::~EdgeCompare()
{
}

bool EdgeCompare::operator()(std::shared_ptr<Edge> p1, std::shared_ptr<Edge> p2)
{
	if (p1->weight > p2->weight) return true;
	if (p1->weight < p2->weight) return false;

	return false;
}
