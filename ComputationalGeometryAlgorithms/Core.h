#pragma once
#include <cmath>
#include <limits>

constexpr float TOLERANCE = 0.0000001f;

template<typename T>
constexpr T INF = std::numeric_limits<T>::infinity();

const float PI = 3.1415926f;

enum class RelativePosition
{
	LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
};

inline bool isEqualD(float x, float y)
{
	return std::fabs(x - y) < TOLERANCE;
}

/*
*
*  a    b  xor (false when both are 0 or both are 1)
	0	0	0
	1	1	0
	0	1	1
	1	0	1

*/
inline bool _xor(bool a, bool b)
{
	return a ^ b;
}

inline float radianToDegree(float radian)
{
	return float((radian * 180) / PI);
}

inline float degreeToRadian(float degree)
{
	return float((degree * PI) / 180);
}