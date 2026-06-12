#pragma once
#include "GeoUtils.h"

namespace HalfEdgeImpl
{

static int _id;
template<typename T = float, size_t dim = DIM3>
struct HalfEdge;

template<typename T = float, size_t dim = DIM3>
struct Face;

template<typename T = float, size_t dim = DIM3>
struct Vertex
{
	Vector<T, dim> point;
	HalfEdge<T, dim>* incidentEdge = nullptr;

	Vertex(Vector<T, dim>& _point) : point(_point){}

	void print()
	{
		std::cout << "Vertex:(" << point[X] << "," << point[Y] << ")\n";
	}
};


template<typename T = float, size_t dim = DIM3>
struct HalfEdge
{
	Vector<T, dim>* origin = nullptr;
	HalfEdge<T, dim>* twin = nullptr;
	HalfEdge<T, dim>* next = nullptr;
	HalfEdge<T, dim>* prev = nullptr;
	Face<T, dim>* incidentFace = nullptr;
	int id;

	HalfEdge() : id(-1) {}
	HalfEdge(Vector<T, dim>& _origin) : origin(_origin) { id = _id++; }

	Vector<T, dim>* destination()
	{
		return twin->origin;
	}

	void print()
	{
		std::cout << "Vertex:(" << point[X] << "," << point[Y] << ")\n";
	}
};

template<typename T = float, size_t dim = DIM3>
struct Face
{
	HalfEdge<T, dim>* outer = nullptr; // pointer to one halfedge of the outer boundary
	std::vector<HalfEdge<T, dim>*> inner; //pointer to one halfedge of each of inner holes
	
};

template<typename T = float, size_t dim = DIM3>
struct Polygon
{
	typedef Vector<T, dim> VectorNf;
	std::vector<Vertex<T, dim>*> vertices;
	std::vector<HalfEdge<T, dim>*> halfEdges;
	std::vector<Face<T, dim>*> faces;

	std::vector<Vertex<T, dim>*> getVertices() { return vertices;  }
	std::vector<HalfEdge<T, dim>*> getHalfedges() { return halfEdges; }
	std::vector<Face<T, dim>*> getFaces() { return faces; }
	Vertex<T, dim>* getVertex(VectorNf& _point);

public:
	//Construct double connected edge list using the given points.
	//Assume the points are in counterclockwise order.
	Polygon(std::vector<VectorNf>&);
};





template<typename T, size_t dim>
Polygon<T, dim>::Polygon(std::vector<VectorNf>& _points)
{
	size_t size = points.size();

	//Polygon should have atleast 3 vertices
	if (size < 3) return;

	for (size_t j = 0; j < size; ++j)
	{
		vertices.push_back(new Vertex<T, dim>(_points[j]));
	}

	for (size_t j = 0; j <= vertices.size() - 2; ++j)
	{
		auto hedge = new HalfEdge<T, dim>(vertices[j]);
		auto hedgeTwin = new HalfEdge<T, dim>(vertices[j + 1]);

		vertices[i]->incidentEdge = hEdge;
		hEdge->twin = hedgeTwin;

		halfEdges.push_back(hedge);
		halfEdges.push_back(hedgeTwin);
	}

	auto hedge = new HalfEdge<T, dim>(vertices.back());
	auto hedgeTwin = new HalfEdge<T, dim>(vertices.front());
	hEdge->twin = hedgeTwin;
	hedgeTwin->twin = hedge;
	halfEdges.push_back(hedge);
	halfEdges.push_back(hedgeTwin);

	vertices[vertices.size() - 1]->incidentEdge = hedge;

	for (size_t j = 2; j <= halfEdges.size() - 3; ++j)
	{
		if (j % 2 == 0)
		{
			halfEdges[j]->next = halfEdges[j + 2];
			halfEdges[j]->prev = halfEdges[j - 2];
		}
		else
		{
			halfEdges[j]->next = halfEdges[j - 2];
			halfEdges[j]->prev = halfEdges[j + 2];
		}
	}

	halfEdges[0]->next = halfEdges[2];
	halfEdges[0]->prev = halfEdges[halfEdges.size() - 2];
	halfEdges[1]->next = halfEdges[halfEdges.size() - 1];
	halfEdges[1]->prev = halfEdges[3];


	halfEdges[halfEdges.size() - 2]->next = halfEdges[0];
	halfEdges[halfEdges.size() - 2]->prev = halfEdges[halfEdges.size() - 4];
	halfEdges[halfEdges.size() - 1]->next = halfEdges[halfEdges.size() - 3];
	halfEdges[halfEdges.size() - 1]->prev = halfEdges[1];

	//f1 represents the polygon inner face which is bounded by the edges. 
	//f2 represents the outer unbounded polygon for which f1 is hole. f2->inner keeps the clockwise edges.
	//f2->outer is null since it is unbounded. To check whether polygon is interior of the polygon just
	//check the outer pointer. 
	Face<T, dim>* f1 = new Face<T, dim>();
	Face<T, dim>* f2 = new Face<T, dim>();

	faces.push_back(f1);
	faces.push_back(f2);

	f1->outer = halfEdges[0];
	f2->inner.push_back(halfEdges[1]);

	f1->outer->incidentFace = f1;
	Edge<T, dim>* edge = f1->outer->next;
	while (edge != f1->outer)
	{
		edge->incidentFace = f1;
		edge = edge->next;
	}

	//f2->inner has half edges connect in clockwise order
	f2->inner[0]->incidentFace = f2;
	edge = f2->inner[0]->next;
	while (edge != f2->inner[0])
	{
		edge->incidentFace = f2;
		edge = edge->next;
	}
}

template<typename T, size_t dim>
Vertex<T, dim>* Polygon<T, dim>::getVertex(VectorNf& _point)
{
	for (auto vertex : vertices)
	{
		if (vertex->point == _point)
			return vertex;
	}
	return nullptr;
}

}//namespace