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

		constexpr auto MIN_FLOAT = std::numeric_limits<float>::min();

		if (MIN_FLOAT < lensq && lensq <= 1)
		{
			return p / std::sqrt(lensq);
		}
	}
} 

inline Vector3f randomOnHemisphere(const Vector3f& normal)
{
	auto randomVec = randomUnitVec();

	if (randomVec.dot(normal) > 0.0f)
	{
		return randomVec;
	}
	else
		return -randomVec;

}

/*To get the reflected ray, find projection of incoming ray v onto normal n. normal n is unit length.
 scale n 2 times of the projection magnitude and subtract from vector v which is pointed inside the
 surface.
*/

inline Vector3f reflect(const Vector3f& v, const Vector3f& n)
{
	return v - (n * v.dot(n) * 2);
}

