#pragma once
#include <vector>
#include <string>

enum class NodeColor
{
	WHITE, //not visited
	GREY, //visited
	BLACK //done
};

struct vertex
{
	int id; //unique identifier for each node with same value.
	std::string value; //stores name of city, name of person etc

	//stores pointer to the adjacent vertex and weight of the edge to the vertex
	std::vector<std::pair<vertex*, int>> adjList; 

	NodeColor color = NodeColor::WHITE;
	int distance;
	vertex* predecessor;

	vertex() {}
	vertex(int _id, const std::string& _value = "") : id(_id), value(_value) {}
};

/*vertex numbering should start from 0.*/
class GraphAdjMatrix
{
private:
	int** m_adjacencyMatrix;
	int m_numVertices, m_numEdges;

public:

	GraphAdjMatrix(int numVertices = 10);
	~GraphAdjMatrix();

	void addEdge(int v1, int v2, int weight);
	void deleteEdge(int v1, int v2);
	void printGraph();
};

class GraphAdjList
{
public:
	GraphAdjList(){}
	void addNode(int _id, const std::string& _value = "");
	void addEdge(int v1, int v2, int weight = 0);
	void bfs(int sourceVertexID);
	void dfs(int sourceVertexID);
	bool ssspBellmanFord(int source);
private:
	vertex* initializeAndFindVertex(int sourceVertexID);
	vertex* initializeGraphForBellmanFord(int sourceVertexID);
private:
	std::vector<vertex*> m_vertices;
	
};