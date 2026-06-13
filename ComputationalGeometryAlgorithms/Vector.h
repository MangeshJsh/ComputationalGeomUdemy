#pragma once

#include "Core.h"

#include <iostream>
#include <array>

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

	Vector(coordinate_type _x, coordinate_type _y, coordinate_type _z) : coords({_x, _y, _z}) {}

	Vector(coordinate_type _x, coordinate_type _y) : coords({ _x, _y }) {}

	//Equality check
	bool operator==(const Vector<coordinate_type, dimension>&) const;

	//Not Equal
	bool operator!=(const Vector<coordinate_type,dimension>&) const;

	//Addition
	Vector<coordinate_type, dimension> operator+(const Vector<coordinate_type, dimension>&) const;

	//Subtraction
	Vector<coordinate_type, dimension> operator-(const Vector<coordinate_type, dimension>&) const;

	//Scalar multiplication
	Vector<coordinate_type, dimension> operator*(double scale) const;

	Vector<coordinate_type, dimension>& operator+=(const Vector<coordinate_type, dimension>& rhs);

	Vector<coordinate_type, dimension>& operator-=(const Vector<coordinate_type, dimension>& rhs);

	Vector<coordinate_type, dimension>& operator*=(double t);

	Vector<coordinate_type, dimension>& operator/=(double t);

	Vector<coordinate_type, dimension> operator/(double t);

	//Less than operator
	bool operator <(const Vector<coordinate_type, dimension>&);

	//Greater than operator
	bool operator >(const Vector<coordinate_type, dimension>&);

	//Indexing operator
	coordinate_type operator[](int) const;

	//Assign value to a dimension
	void assign(int dim, coordinate_type value);

	//dot product
	float dot(const Vector<coordinate_type, dimension>&);

	//magnitude
	float length() const;

	float length_squared() const;

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
	return Vector(coords[0] + rhs.coords[0], coords[1] + rhs.coords[1], coords[2] + rhs.coords[2]);
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator-(const Vector<coordinate_type, dimension>& rhs) const
{
	return Vector(coords[0] - rhs.coords[0], coords[1] - rhs.coords[1], coords[2] - rhs.coords[2]);
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator+=(const Vector<coordinate_type, dimension>& rhs)
{
	coords[0] += rhs.coords[0];
	coords[1] += rhs.coords[1];
	coords[2] += rhs.coords[2];
	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator-=(const Vector<coordinate_type, dimension>& rhs) 
{
	coords[0] -= rhs.coords[0];
	coords[1] -= rhs.coords[1];
	coords[2] -= rhs.coords[2];
	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator*=(double t)
{
	coords[0] *= t;
	coords[1] *= t;
	coords[2] *= t;
	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension>& Vector<coordinate_type, dimension>::operator/=(double t)
{
	coords[0] /= t;
	coords[1] /= t;
	coords[2] /= t;
	return *this;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator/(double t)
{
	return Vector3f(coords[0] / t, coords[1] / t, coords[2] / t);
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
coordinate_type Vector<coordinate_type, dimension>::operator[](int index) const
{
	if (index >= coords.size())
	{
		std::cout << "Index out of bound";
		return coordinate_type();
	}

	return coords[index];
}

template<typename coordinate_type, size_t dimension>
void Vector<coordinate_type, dimension>::assign(int dim, coordinate_type value)
{
	if (dim >= coords.size())
	{
		std::cout << "Index out of bound";
		return;
	}
	coords[dim] = value;
}


template<typename coordinate_type, size_t dimension>
float Vector<coordinate_type, dimension>::dot(const Vector<coordinate_type, dimension>& rhs)
{
	if (coords.size() != rhs.coords.size()) return FLT_MIN;

	return (coords[0] * rhs.coords[0] + coords[1] * rhs.coords[1] + coords[2] * rhs.coords[2]);
}

template<typename coordinate_type, size_t dimension>
float Vector<coordinate_type, dimension>::length() const
{
	float sum;
	for (size_t i = 0; i < dimension; ++i)
	{
		sum += coords[i] * coords[i];
	}
	return std::sqrt(sum);
}

template<typename coordinate_type, size_t dimension>
float Vector<coordinate_type, dimension>::length_squared() const
{
	float sum;
	for (size_t i = 0; i < dimension; ++i)
	{
		sum += coords[i] * coords[i];
	}
	return sum;
}


template<typename coordinate_type, size_t dimension>
void Vector<coordinate_type, dimension>::normalize()
{
	float mag = length();
	if (mag == 0.0) return;
	coords[0] /= mag;
	coords[1] /= mag;
	coords[2] /= mag;
}

template<typename coordinate_type, size_t dimension>
Vector<coordinate_type, dimension> Vector<coordinate_type, dimension>::operator*(double scale) const
{
	return Vector<coordinate_type, dimension>(coords[0] * scale, coords[1] * scale, coords[2] * scale);
}

float crossProduct2D(Vector2f v1, Vector2f v2);

Vector3f crossProduct3D(Vector3f v1, Vector3f v2);

float scalarTripleProduct(Vector3f v1, Vector3f v2, Vector3f v3);