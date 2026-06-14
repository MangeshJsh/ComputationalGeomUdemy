#pragma once
#include "Core.h"

template<typename T>
class Interval
{
	T m_min, m_max;

public:

	using INFT = INF<T>;
	Interval() : m_min(+INFT), m_max(-INFT){} // default interval is empty

	Interval(T min, T max) : m_min(min), m_max(max) {}

	T size() { return m_max - m_min; }

	bool contains(T x)
	{
		return (x >= m_min && x <= m_max);
	}

	bool surrounds(T x)
	{
		return (x > m_min && x < m_max);
	}
	
	static constexpr Interval empty{ +INFT, -INFT };

	static constexpr Interval universe{ -INFT, +INFT };
};
