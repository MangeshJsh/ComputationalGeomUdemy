#pragma once

#include <cstdlib>


inline float randomf()
{
	return float(std::rand() / (RAND_MAX + 1.0));
}

inline float randomf(float min, float max)
{
	return float(min + (max - min) * randomf());
}