#pragma once

#include "Core.h"

#include <iostream>
#include <array>
#include <climits>

constexpr int DIM2 = 2;
constexpr int DIM3 = 3;

constexpr auto X = 0;
constexpr auto Y = 1;
constexpr auto Z = 2;

template <typename coordinate_type, size_t dimension = DIM3>
class Vector
{

	static_assert(std::is_arithmetic<coordinate_type>::value, "Only integral and floating point types allowed");
	static_assert(dimension >= DIM2, "Vector dimension should be atleast 2");

	std::array<coordinate_type, dimension> coords;

public:

	Vector() = default;

	Vector(const std::array<coordinate_type, dimension>& _coords) : coords(_coords) {}

	template <size_t D = dimension,
		typename = std::enable_if_t<D == 2>>
		Vector(coordinate_type _x, coordinate_type _y)
		: coords{ _x, _y }
	{
	}

	template <size_t D = dimension,
		typename = std::enable_if_t<D == 3>>
		Vector(coordinate_type _x, coordinate_type _y, coordinate_type _z)
		: coords{ _x, _y, _z }
	{
	}

	//Equality check
	bool operator==(const Vector<coordinate_type, dimension>&) const;

	//Not Equal
	bool operator!=(const Vector<coordinate_type,dimension>&) const;

	//Addition
	Vector<coordinate_type, dimension> operator+(const Vector<coordinate_type, dimension>&) const;

	//Subtraction
	Vector<coordinate_type, dimension> operator-(const Vector<coordinate_type, dimension>&) const;

	//Scalar multiplication
	Vector<coordinate_type, dimension> operator*(coordinate_type scale) const;

	Vector<coordinate_type, dimension>& operator+=(const Vector<coordinate_type, dimension>& rhs);

	Vector<coordinate_type, dimension>& operator-=(const Vector<coordinate_type, dimension>& rhs);

	Vector<coordinate_type, dimension>& operator*=(coordinate_type t);

	Vector<coordinate_type, dimension>& operator/=(coordinate_type t);

	Vector<coordinate_type, dimension> operator/(coordinate_type t);

	Vector<coordinate_type, dimension> operator-() const
	{
		Vector<coordinate_type, dimension> temp;
		for (size_t i = 0; i < dimension; ++i)
		{
			temp.assign(i, -coords[i]);
		}
		return temp;
	}

	//Less than operator
	bool operator <(const Vector<coordinate_type, dimension>&);

	//Greater than operator
	bool operator >(const Vector<coordinate_type, dimension>&);

	//Indexing operator
	coordinate_type operator[](size_t) const;

	//Assign value to a dimension
	void assign(size_t dim, coordinate_type value);

	//dot product
	coordinate_type dot(const Vector<coordinate_type, dimension>&) const;

	//magnitude
	coordinate_type length() const;

	coordinate_type length_squared() const;

	//normalize
	void normalize();

	friend std::ostream& operator<<(std::ostream& out, const Vector<coordinate_type, dimension>& vec)
	{
		for (size_t i = 0; i < coords.size(); ++i)
		{
			std::cout << coords[i] << " ";
		}
		return out;
	}
};


using Vector2f = Vector<float, DIM2>;
using Vector3f = Vector<float, DIM3>;


template<typename coordinate_type, size_t dimension>
bool Vector<coordinate_type, dimension>::operator==(const Vector<coordinate_type, dimension>& rhs) const
{

	for (size_t i = 0; i < dimension; ++i)
	{
		if (!isEqualD(coords[i], rhs.coords[i])) return false;
	}

	return true;
}

template<typename coordinate_type, size_t dimension>
bool Vector<coordinate_type, dimension>::operator!=(const Vector<coordinate_type, dimension>& rhs) const
{
	return !(*this == rhs);
}


template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator+(const Vector<coordinate_type, dimension>& rhs) const
{
	Vector<coordinate_type, dimension> temp;

	for (size_t i = 0; i < dimension; ++i)
	{
		temp.assign(i, coords[i] + rhs.coords[i]);
	}

	return temp;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator-(const Vector<coordinate_type, dimension>& rhs) const
{

	Vector<coordinate_type, dimension> temp;

	for (size_t i = 0; i < dimension; ++i)
	{
		temp.assign(i, coords[i] - rhs.coords[i]);
	}

	return temp;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator+=(const Vector<coordinate_type, dimension>& rhs)
{
	for (size_t i = 0; i < dimension; ++i)
	{
		coordinate_type val = coords[0] + rhs.coords[0];
		assign(i, val);
	}
	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator-=(const Vector<coordinate_type, dimension>& rhs) 
{
	for (size_t i = 0; i < dimension; ++i)
	{
		coordinate_type val = coords[0] - rhs.coords[0];
		assign(i, val);
	}
	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator*=(coordinate_type t)
{
	for (size_t i = 0; i < dimension; ++i)
	{
		coordinate_type val = coords[0] * t;
		assign(i, val);
	}

	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator/=(coordinate_type t)
{
	for (size_t i = 0; i < dimension; ++i)
	{
		coordinate_type val = coords[0] / t;
		assign(i, val);
	}

	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator/(coordinate_type t)
{
	Vector<coordinate_type, dimension> temp;

	for (size_t i = 0; i < dimension; ++i)
	{
		temp.assign(i, coords[i] / t);
	}

	return temp;
}

template<typename coordinate_type, size_t dimension>
bool Vector<coordinate_type, dimension>::operator <(const Vector<coordinate_type, dimension>& rhs)
{
	for (size_t i = 0; i < dimension; ++i)
	{
		if (coords[i] < rhs.coords[i])
			return true;
		else if (coords[i] > rhs.coords[i])
			return false;
	 }

	return false;
}

template<typename coordinate_type, size_t dimension>
bool Vector<coordinate_type, dimension>::operator >(const Vector<coordinate_type, dimension>& rhs)
{
	for (size_t i = 0; i < dimension; ++i)
	{
		if (coords[i]  > rhs.coords[i])
			return true;
		else if (coords[i] < rhs.coords[i])
			return false;
	}

	return false;
}

template<typename coordinate_type, size_t dimension>
coordinate_type Vector<coordinate_type, dimension>::operator[](size_t index) const
{
	if (index >= coords.size())
	{
		std::cout << "Index out of bound";
		return coordinate_type();
	}

	return coords[index];
}

template<typename coordinate_type, size_t dimension>
void Vector<coordinate_type, dimension>::assign(size_t dim, coordinate_type value)
{
	if (dim >= coords.size())
	{
		std::cout << "Index out of bound";
		return;
	}
	coords[dim] = value;
}


template<typename coordinate_type, size_t dimension>
coordinate_type Vector<coordinate_type, dimension>::dot(const Vector<coordinate_type, dimension>& rhs) const
{
	if (coords.size() != rhs.coords.size()) return std::numeric_limits<coordinate_type>::min();

	coordinate_type sum{};

	for (size_t i = 0; i < dimension; ++i)
	{
		sum += coords[i] * rhs.coords[i];
	}

	return sum;
}

template<typename coordinate_type, size_t dimension>
coordinate_type Vector<coordinate_type, dimension>::length() const
{
	coordinate_type sum{};
	for (size_t i = 0; i < dimension; ++i)
	{
		sum += coords[i] * coords[i];
	}
	return std::sqrt(sum);
}

template<typename coordinate_type, size_t dimension>
coordinate_type Vector<coordinate_type, dimension>::length_squared() const
{
	coordinate_type sum{};
	for (size_t i = 0; i < dimension; ++i)
	{
		sum += coords[i] * coords[i];
	}
	return sum;
}


template<typename coordinate_type, size_t dimension>
void Vector<coordinate_type, dimension>::normalize()
{
	coordinate_type mag = length();
	if (mag == 0.0) return;

	for (size_t i = 0; i < dimension; ++i)
	{
		assign(i, coords[i]/mag);
	}	
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator*(coordinate_type scale) const
{
	Vector<coordinate_type, dimension> temp;

	for (size_t i = 0; i < dimension; ++i)
	{
		temp.assign(i, coords[i] * scale);
	}

	return temp;
}

float crossProduct2D(Vector2f v1, Vector2f v2);

Vector3f crossProduct3D(Vector3f v1, Vector3f v2);

float scalarTripleProduct(Vector3f v1, Vector3f v2, Vector3f v3);