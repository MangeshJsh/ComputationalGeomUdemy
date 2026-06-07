#pragma once
#include "Vector.h"

template<typename coordinate_type, size_t dim = DIM3>
class Line
{
	Vector<coordinate_type, dim> start;
	Vector<coordinate_type, dim> end;
	Vector<coordinate_type, dim> dir;

public:
	Line(const Vector<coordinate_type, dim>& _start, const Vector<coordinate_type, dim>& _end)
	{
		start = _start;
		end = _end;
		dir = p2 - p1;
	}

	Line(Vector<coordinate_type, dim>& _start, Vector<coordinate_type, dim>& _dir)
	{
		start = _start;
		dir = _dir;
		end = start + dir;
	}

	Vector<coordinate_type, dim> startPoint() const { return start; }
	Vector<coordinate_type, dim> endPoint() const { return end; }
	Vector<coordinate_type, dim> direction() const { return dir; }
};

