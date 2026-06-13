#pragma once
#include <cmath>

constexpr double TOLERANCE = 0.0000001;
constexpr double PI = 3.14159;

enum class RelativePosition
{
	LEFT, RIGHT, BEHIND, BEYOND, BETWEEN, ORIGIN, DESTINATION
};

static bool isEqualD(double x, double y)
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
static bool _xor(bool a, bool b)
{
	return a ^ b;
}

float radianToDegree(float radian)
{
	return float((radian * 180) / PI);
}

float degreeToRadian(float degree)
{
	return float((degree * PI) / 180);
}