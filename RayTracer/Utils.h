#pragma once

#include <cstdlib>
#include <random>
#include <limits>

inline float randomf()
{
	return float(std::rand() / (RAND_MAX + 1.0));
}

inline float randomf(float min, float max)
{
	return float(min + (max - min) * randomf());
}

inline float generateRandomNumber()
{
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float generateRandomNumber(float min, float max)
{
	return min + (max - min) * generateRandomNumber();
}

inline Vector3f randomVec()
{
	return Vector3f(generateRandomNumber(), generateRandomNumber(), generateRandomNumber());
}

inline Vector3f randomVec(float min, float max)
{
	return Vector3f(generateRandomNumber(min, max), generateRandomNumber(min, max), generateRandomNumber(min, max));
}

inline Vector3f randomUnitVec()
{
	while (true)
	{
		auto p = randomVec(-1.0f, 1.0f);
		auto lensq = p.length_squared();

		const auto MIN_FLOAT = std::numeric_limits<float>::min();

		if (MIN_FLOAT < lensq && lensq <= 1)
		{
			return p / std::sqrt(lensq);
		}
	}
}