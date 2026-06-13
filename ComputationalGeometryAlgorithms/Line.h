#pragma once
#include "Vector.h"

template<typename coordinate_type, size_t dim = DIM3>
class Line
{
	Vector<coordinate_type, dim> m_start;
	Vector<coordinate_type, dim> m_end;
	Vector<coordinate_type, dim> m_dir;

public:
	Line(const Vector<coordinate_type, dim>& _start, const Vector<coordinate_type, dim>& _end)
	{
		m_start = _start;
		m_end = _end;
		m_dir = _end - _start;
	}

	Line(Vector<coordinate_type, dim>& _start, Vector<coordinate_type, dim>& _dir)
	{
		m_start = _start;
		m_dir = _dir;
		m_end = _start + _dir;
	}

	Vector<coordinate_type, dim> startPoint() const { return m_start; }
	Vector<coordinate_type, dim> endPoint() const { return m_end; }
	Vector<coordinate_type, dim> direction() const { return m_dir; }
};

