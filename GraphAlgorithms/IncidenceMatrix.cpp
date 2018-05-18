#include "stdafx.h"
#include "IncidenceMatrix.h"
//#include "GraphAlgorithms.cpp"

extern int checkInt(int min, int max);

IncidenceMatrix::IncidenceMatrix()
{
}

IncidenceMatrix::IncidenceMatrix(int _size, float _density, bool _directed)
{
	this->density = _density;
	this->size = _size + 1;								//rozmiar o jeden wi�kszy od okre�lonego, gdy� w ostatnim wierszu b�d� wagi
	this->directed = _directed;
	this->edgeNum = (density * (size - 1) * (size - 2)) / 2;
	for (int i = 0; i < size; i++)
	{
		std::vector<int> vec(edgeNum);
		graph.push_back(vec);
		for (int j = 0; j < edgeNum; j++)
		{
			graph[i][j] = 0;
		}
	}
}

IncidenceMatrix::IncidenceMatrix(int _size, bool _directed, int edges)
{
	this->edgeNum = edges;
	this->size = _size + 1;								//rozmiar o jeden wi�kszy od okre�lonego, gdy� w ostatnim wierszu b�d� wagi
	this->directed = _directed;
	this->density = 2 * edges / (_size*(_size - 1));
	graph.reserve(size);
	for (int i = 0; i < size; i++)
	{
		std::vector<int> vec(edgeNum);
		graph.push_back(vec);
		for (int j = 0; j < edgeNum; j++)
		{
			graph[i][j] = 0;
		}
	}
}


IncidenceMatrix::~IncidenceMatrix()
{
}

void IncidenceMatrix::addEdge(int begin, int end, int i, int weight)
{
	graph[size - 1][i] = weight;
	graph[begin][i] = 1;
	if (directed)
		graph[end][i] = -1;
	else
		graph[end][i] = 1;
}

void IncidenceMatrix::fillGraph()
{
	int begin, end, weight;
	for (int i = 0; i < edgeNum; i++)
	{
		std::cout << "Input the beggining vertex: ";
		begin = checkInt(0, size - 2);

		std::cout << "Input the ending vertex: ";
		end = checkInt(0, size - 2);

		std::cout << "Input the weight of the edge: ";
		weight = checkInt(0, 100);

		addEdge(begin, end, i, weight);
	}
}

void IncidenceMatrix::randomFillGraph()
{
	int prev = 0, j = 0, next, weight;
	std::vector<int> visited;

	visited.push_back(prev);
	srand(time(NULL));
	
	for (int i = 0; i < (size - 2); i++)
	{
		next = rand() % (size - 1);
		while (j < visited.size())
		{
			if (next == visited[j])
			{
				next = (next + 1) % (size - 1);
				j = 0;
			}
			else
				j++;
		}
		j = 0;
		weight = rand() % 100;
		addEdge(prev, next, i, weight);
		prev = next;
		visited.push_back(prev);
	}
	for (int i = (size - 2); i < edgeNum; i++)
	{
		prev = rand() % (size - 1);
		next = rand() % (size - 1);
		while (prev == next)
		{
			next = rand() % (size - 1);
		}
		weight = rand() % 100;
		addEdge(prev, next, i, weight);
	}
}

IncidenceMatrix * IncidenceMatrix::readGraphFromFile(std::string fileName, bool direct)
{
	std::fstream file;
	std::string line;
	int siz, edges, v1, v2, weight, i = 0;

	file.open(fileName, std::ios::in);
	if (file.good())
	{
		getline(file, line);
		std::istringstream iss(line);
		iss >> siz; iss >> edges;

		IncidenceMatrix *matrix = new IncidenceMatrix(siz, direct, edges);

		std::istringstream iss2;
		while (getline(file, line))
		{
			std::istringstream iss2(line);
			iss2 >> v1; iss2 >> v2; iss2 >> weight;
			matrix->addEdge(v1, v2, i, weight);
			i++;
		}
		return matrix;
	}
	else return nullptr;
}

void IncidenceMatrix::display()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < edgeNum; j++)
		{
			std::cout << graph[i][j] << " ";
		}
		std::cout << "\n";
	}
}

NeighboursList * IncidenceMatrix::primAlgorithm(IncidenceMatrix * inGraph)
{
	std::shared_ptr<Edge> edge;
	std::vector<bool> visited(inGraph->size-1);
	for (int i = 0; i < visited.size(); i++) visited[i] = false;

	std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge> >, EdgeCompare > queue;
	NeighboursList *spanningTree = new NeighboursList((inGraph->size-1), false, (inGraph->size - 2));
	int v, k, inSize = inGraph->size;
	std::vector<std::shared_ptr<Edge> > tmp;

	for (int i = 0; i < inGraph->edgeNum; i++)
	{
		k = 0;
		std::vector<int> tmpEdge(3);
		for (int j = 0; j < inSize - 1; j++)
		{

			if (inGraph->graph[j][i] == 0) continue;
			else
			{
				tmpEdge[k] = j;
				k++;
			}
		}
		tmpEdge[2] = inGraph->graph[inSize - 1][i];
		std::shared_ptr<Edge> e(new Edge(tmpEdge[0], tmpEdge[1], tmpEdge[2]));
		std::shared_ptr<Edge> re(new Edge(tmpEdge[1], tmpEdge[0], tmpEdge[2]));
		tmp.push_back(e);
		tmp.push_back(re);
		
	}
	v = 0;
	visited[0] = true;

	for (int j = 0; j < spanningTree->size - 1; j++)
	{
		for (int l = 0; l < tmp.size(); l++)
		{
			if ((tmp[l]->beginVertex == v) && !visited[tmp[l]->endVertex])
				queue.push(tmp[l]);
		}
		do
		{
			edge = queue.top();
			queue.pop();
		} while (visited[edge->endVertex]);

		spanningTree->graph[edge->beginVertex].push_front(edge);
		visited[edge->endVertex] = true;
		v = edge->endVertex;
	}

	return spanningTree;
}
