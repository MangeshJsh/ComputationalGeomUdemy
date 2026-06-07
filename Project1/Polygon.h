#pragma once

#include "Vector.h"
#include "Point.h"

#include <list>
#include <vector>

template<typename T, size_t dim>
struct Vertex
{
	Vector<T, dim> point;
	Vertex* next;
	Vertex* prev;

	Vertex(Vector<T,dim>& _point, Vertex<T,dim>* _next = nullptr, Vertex<T, dim>* _prev = nullptr):
		point(_point), next(_next), prev(_prev){}
};

typedef Vertex<float, DIM2> Vertex2d;
typedef Vertex<float, DIM3> Vertex3d;


template<typename T, size_t dim = DIM3>
class Polygon
{
	std::vector<Vertex<T, dim>*> vertex_list;

public:
	Polygon(std::list<Vector<T, dim>>& points)
	{
		const int size = points.size();

		if (size < 3)
		{
			std::cout << "not enough points to construct a polygon" << std::endl;
			return;
		}

		for (auto point : points)
		{
			vertex_list.push_back(new Vertex(point));
		}

		for (int i = 0; i < size; ++i)
		{
			
			vertex_list[i]->next = &vertex_list[(i+1)%size];
			if (i == 0)
			{
				vertex_list[i]->prev = &vertex_list[size - 1];
			}
			else
			{
				vertex_list[i]->prev = &vertex_list[i - 1];
			}
			
		}
	}

	std::vector<Vertex<T, dim>*> getVertices() {
		return vertex_list;
	}

};

typedef Polygon<float, DIM3> PolygonS3d;
typedef Polygon<float, DIM2> PolygonS2d;