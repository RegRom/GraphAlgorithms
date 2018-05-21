#include "stdafx.h"
#include "NeighboursList.h"

extern int checkInt(int min, int max);

NeighboursList::NeighboursList()
{
}

NeighboursList::NeighboursList(int _size, float _density, bool _directed)
{
	this->density = _density;
	this->size = _size;
	this->directed = _directed;
	this->edgeNum = (density * (size) * (size - 1)) / 2;
	for (int i = 0; i < size; i++)
	{
		std::list<std::shared_ptr<Edge> > list;
		graph.push_back(list);
	}
}

NeighboursList::NeighboursList(int _size, bool _directed, int edges)
{
	this->edgeNum = edges;
	this->size = _size;								
	this->directed = _directed;
	this->density = 2 * edges / (_size*(_size - 1));
	for (int i = 0; i < size; i++)
	{
		std::list<std::shared_ptr<Edge> > list;
		graph.push_back(list);
	}
}


NeighboursList::~NeighboursList()
{
}

void NeighboursList::addEdge(int begin, int end, int weight)
{
	std::shared_ptr<Edge> edge(new Edge(begin, end, weight));
	graph[begin].push_front(edge);

	if (!directed)
	{
		std::shared_ptr<Edge> reverse_edge(new Edge(end, begin, weight));
		graph[end].push_front(reverse_edge);
	}
}

void NeighboursList::fillGraph()
{
	int begin, end, weight;
	for (int i = 0; i < edgeNum; i++)
	{
		std::cout << "Input the beggining vertex: ";
		begin = checkInt(0, size - 1);

		std::cout << "Input the ending vertex: ";
		end = checkInt(0, size - 1);

		std::cout << "Input the weight of the edge: ";
		weight = checkInt(0, 100);

		addEdge(begin, end, weight);
	}
}

void NeighboursList::randomFillGraph()
{
	int prev = 0, j = 0, next, weight;
	std::vector<int> visited;

	visited.push_back(prev);
	srand(time(NULL));

	for (int i = 0; i < (size - 1); i++)
	{
		next = rand() % size;
		while (j < visited.size())
		{
			if (next == visited[j])
			{
				next = (next + 1) % size;
				j = 0;
			}
			else
				j++;
		}
		j = 0;
		weight = rand() % 100;
		addEdge(prev, next, weight);
		prev = next;
		visited.push_back(prev);
	}
	for (int i = (size - 1); i < edgeNum; i++)
	{
		prev = rand() % size;
		next = rand() % size;
		while (prev == next)
		{
			next = rand() % size;
		}
		weight = rand() % 100;
		addEdge(prev, next, weight);
	}
}

NeighboursList * NeighboursList::readGraphFromFile(std::string fileName, bool direct)
{
	std::fstream file;
	std::string line;
	int siz, edges, v1, v2, weight;

	file.open(fileName, std::ios::in);
	if (file.good())
	{
		getline(file, line);
		std::istringstream iss(line);
		iss >> siz; iss >> edges;

		NeighboursList *list = new NeighboursList(siz, direct, edges);

		std::istringstream iss2;
		while (getline(file, line))
		{
			std::istringstream iss2(line);
			iss2 >> v1; iss2 >> v2; iss2 >> weight;
			list->addEdge(v1, v2, weight);
		}
		return list;
	}
	else
	{
		std::cout << "\nFile is corrupted!\n";
		getchar();
		return nullptr;
	}
}

void NeighboursList::display()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i << "->";
		for (std::shared_ptr<Edge> v : graph[i])
		{
			std::cout << v->endVertex << "(" << v->weight << ")" << " ";
		}
		std::cout << "\n";
	}
}

NeighboursList * NeighboursList::primAlgorithm(NeighboursList * inGraph)
{
	std::shared_ptr<Edge> edge;
	std::vector<bool> visited(inGraph->size);
	for (int i = 0; i < visited.size(); i++) visited[i] = false;

	std::priority_queue<std::shared_ptr<Edge>, std::vector<std::shared_ptr<Edge> >, EdgeCompare> queue;
	NeighboursList *spanningTree = new NeighboursList(inGraph->size, false, (inGraph->size - 1));
	int v = 0;
	visited[0] = true;

	for (int j = 0; j < spanningTree->size-1; j++)
	{
		for (std::shared_ptr<Edge> e : inGraph->graph[v])
		{
			if(!visited[e->endVertex]) 
				queue.push(e);
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

void NeighboursList::dijkstraAlgorithm(NeighboursList * inGraph, int begin, int end)
{
	const int MAXINT = 2147483647;
	int v;
	std::vector<int> d(inGraph->size), p(inGraph->size);
	std::list<int> path;

	for (int i = 0; i < d.size(); i++)
	{
		p[i] = -1;
		d[i] = MAXINT;
	}

	std::set< std::pair<int, int> > vertices;

	vertices.insert(std::make_pair(0, begin));
	d[begin] = 0;

	while (!vertices.empty())
	{
		std::pair<int, int> tmp = *(vertices.begin());
		vertices.erase(vertices.begin());

		int vertex = tmp.second;
		if (vertex == end) break;

		for (std::shared_ptr<Edge> e : inGraph->graph[vertex])
		{
			int neigh = e->endVertex;
			int weight = e->weight;

			if (d[neigh] > d[vertex] + weight)
			{
				if (d[neigh] != MAXINT)
					vertices.erase(vertices.find(std::make_pair(d[neigh], neigh)));

				d[neigh] = d[vertex] + weight;
				vertices.insert(std::make_pair(d[neigh], neigh));
				p[neigh] = vertex;
			}

		}
	}
	v = end;
	path.push_front(end);
	
	while (v != begin)
	{
		path.push_front(p[v]);
		v = p[v];
	}

	for (int e : path)
	{
		std::cout << e << " ";
	}
	getchar();
	
}

int NeighboursList::getSize()
{
	return this->size;
}
