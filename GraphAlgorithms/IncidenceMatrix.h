#pragma once
class IncidenceMatrix
{
private:
	std::vector< std::vector<int> > graph;
	int size, edgeNum;
	float density;
	bool directed;
public:
	IncidenceMatrix();
	IncidenceMatrix(int _size, float _density, bool _directed);
	IncidenceMatrix(int _size, bool _directed, int edges);
	~IncidenceMatrix();
	void addEdge(int begin, int end, int i, int weight);
	void fillGraph();
	void randomFillGraph();
	IncidenceMatrix *readGraphFromFile(std::string fileName, bool direct);
	void display();
	static IncidenceMatrix *primAlgorithm(IncidenceMatrix *inGraph);
};

