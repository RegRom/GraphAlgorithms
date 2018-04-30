#pragma once
class Edge
{
public:
	int beginVertex, endVertex, weight;

	Edge();
	Edge(int _beginVertex, int _endVertex, int _weight);
	~Edge();
};

