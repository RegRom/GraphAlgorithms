#pragma once
class Edge
{
public:
	int beginVertex, endVertex, weight;


	Edge();
	Edge(int _beginVertex, int _endVertex, int _weight);
	~Edge();
	bool operator<(const std::shared_ptr<Edge> b);
	bool operator>(const std::shared_ptr<Edge> b);
};

struct CompareEdge : public std::binary_function<std::shared_ptr<Edge>, std::shared_ptr<Edge>, bool>
{
	bool operator()(const std::shared_ptr<Edge> lhs, const std::shared_ptr<Edge> rhs) const
	{
		return lhs->weight < rhs->weight;
	}
};
