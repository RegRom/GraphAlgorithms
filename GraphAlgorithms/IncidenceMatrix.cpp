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
	for (int i = (size - 1); i < edgeNum; i++)
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

		IncidenceMatrix *matrix = new IncidenceMatrix(size, direct, edges);

		std::istringstream iss2;
		while (getline(file, line))
		{
			iss2.str(line);
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

IncidenceMatrix * IncidenceMatrix::primAlgorithm(IncidenceMatrix * inGraph)
{
	return nullptr;
}