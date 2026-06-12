#include "GraphAlgo.h"
#include <climits>
#include <iostream>
#include <queue>

GraphAdjMatrix::GraphAdjMatrix(int numVertices) : m_numVertices(numVertices), m_adjacencyMatrix(nullptr)
{
	m_numEdges = 0;

	int** m_adjacencyMatrix = new int* [numVertices];

	for (int i = 0; i < numVertices; ++i)
	{
		m_adjacencyMatrix[i] = new int[numVertices];
	}

	for (int i = 0; i < numVertices; ++i)
	{
		for (int j = 0; j < numVertices; ++j)
		{
			m_adjacencyMatrix[i][j] = INT_MAX;
		}
	}
}

GraphAdjMatrix::~GraphAdjMatrix()
{
	for (int i = 0; i < m_numVertices; ++i)
	{
		delete[] m_adjacencyMatrix[i];
	}
	delete[] m_adjacencyMatrix;
}

void GraphAdjMatrix::addEdge(int v1, int v2, int weight)
{
	if (m_adjacencyMatrix[v1][v2] == INT_MAX)
	{
		++m_numEdges;
	}
	m_adjacencyMatrix[v1][v2] = weight;
}

void GraphAdjMatrix::deleteEdge(int v1, int v2)
{
	if (m_adjacencyMatrix[v1][v2] != INT_MAX)
	{
		--m_numEdges;
	}
	m_adjacencyMatrix[v1][v2] = INT_MAX;
}

void GraphAdjMatrix::printGraph()
{
	for (int i = 0; i < m_numVertices; ++i)
	{
		for (int j = 0; j < m_numVertices; ++j)
		{
			if (m_adjacencyMatrix[i][j] != INT_MAX)
			{
				std::cout << m_adjacencyMatrix[i][j] << " ";
			}
			else
			{
				std::cout << "A";
			}
		}
		std::cout << std::endl;
	}
}

//-------------------------------------------------------------------------------------------------

void GraphAdjList::addNode(int _id, const std::string& _value)
{
	for (const auto& node : m_vertices)
	{
		if (node->id == _id)
		{
			throw std::runtime_error("node with id: " + std::to_string(_id) + "already exists");
		}
		m_vertices.push_back(new vertex(_id, _value));
	}
}

void GraphAdjList::addEdge(int v1ID, int v2ID, int weight = 0)
{
	vertex* v1 = nullptr;
	vertex* v2 = nullptr;

	bool foundV1 = false;
	bool foundV2 = false;

	for (auto node : m_vertices)
	{
		if (node->id == v1ID)
		{
			v1 = node;
			foundV1 = true;
		}

		if (node->id == v2ID)
		{
			v2 = node;
			foundV2 = true;
		}

		if (foundV1 && foundV2)
			break; //edge already exists
	}

	if (foundV1 && foundV2)
	{
		bool edgeAlreadyExists = false;

		for (auto& adjVertex : v1->adjList)
		{
			if (adjVertex.first->id == v2ID)
			{
				edgeAlreadyExists = true;
				break;
				//throw std::runtime_error("Edge between: " + std::to_string(v1ID) + " and " + std::to_string(v2ID) + "already exists");
			}
		}

		if (!edgeAlreadyExists)
		{
			v1->adjList.push_back(std::make_pair(v2, weight));
		}
	}
	else
	{
		std::cout << "Failed adding the edge. One or both vertices does not exist" << std::endl;
	}
}

vertex* GraphAdjList::initializeAndFindVertex(int sourceVertexID)
{
	vertex* sourceNode = nullptr;
	for (auto node : m_vertices)
	{
		if (node->id == sourceVertexID)
		{
			sourceNode = node;
		}
		node->color = NodeColor::WHITE;
		node->distance = -1;
		node->predecessor = nullptr;
	}
	return sourceNode;
}

void GraphAdjList::bfs(int sourceVertexID)
{
	std::queue<vertex*> queue;
	vertex* v1 = initializeAndFindVertex(sourceVertexID);
	if (!v1)
	{
		std::cout << "source vertex does not exist" << std::endl;
		return;
	}
	queue.push(v1);
	
	while (!queue.empty())
	{
		vertex* parentNode = queue.front();
		queue.pop();
		parentNode->color = NodeColor::GREY;

		for (auto node : parentNode->adjList)
		{
			if (node.first->color == NodeColor::WHITE)
			{
				node.first->color = NodeColor::GREY;
				node.first->predecessor = parentNode;
				node.first->distance = parentNode->distance + 1;
				queue.push(node.first);
			}
		}
		parentNode->color = NodeColor::BLACK;
	}
}

void dfsHelper(vertex* node)
{
	node->color = NodeColor::GREY;
	std::cout << node->id << " ";
	for (auto v : node->adjList)
	{
		if (v.first->color == NodeColor::WHITE)
		{
			dfsHelper(v.first);
		}
	}
	node->color = NodeColor::BLACK;
}


void GraphAdjList::dfs(int sourceVertexID)
{
	std::queue<vertex*> queue;
	vertex* v1 = initializeAndFindVertex(sourceVertexID);
	if (!v1)
	{
		std::cout << "source vertex does not exist" << std::endl;
		return;
	}
	dfsHelper(v1);


	//check if any vertex is still unvisited and call dfs on that vertex.
	for (auto v : m_vertices)
	{
		if (v->color == NodeColor::WHITE)
		{
			dfsHelper(v);
			std::cout << std::endl;
		}
	}
}

vertex* GraphAdjList::initializeGraphForBellmanFord(int sourceVertexID)
{
	vertex* sourceNode = nullptr;
	for (auto node : m_vertices)
	{
		node->distance = INT_MAX;
		node->predecessor = nullptr;
		node->color = NodeColor::WHITE;

		if (node->id == sourceVertexID)
		{
			sourceNode = node;
			node->distance = 0;
		}
	}
	return sourceNode;
}

/*
u - start vertex
v - end vertex
weight - end vertex distance
*/

void relax(vertex* u, vertex* v, int weight)
{
	if (v->distance > u->distance + weight)
	{
		v->distance = u->distance + weight;
		v->predecessor = u;
	}
}

bool GraphAdjList::ssspBellmanFord(int source)
{
	vertex* v1 = initializeGraphForBellmanFord(source);
	if (!v1)
	{
		std::cout << "source vertex does not exist" << std::endl;
		return false;
	}

	for (int i = 0; i < m_vertices.size() - 1; ++i)
	{
		for (auto u : m_vertices)
		{
			for (auto v : u->adjList)
			{
				if (u->distance != INT_MAX)
				{
					relax(u, v.first, v.second);
				}
			}

		}
	}

	for (auto u : m_vertices)
	{
		for (auto v : u->adjList)
		{
			if (u->distance != INT_MAX)
			{
				if (v.first->distance > u->distance + v.second)
				{
					return false;
				}
			}
		}

	}
	return true;
}