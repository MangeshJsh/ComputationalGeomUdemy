#pragma once
#include "Core.h"

template<typename T>
class Interval
{
public:

	T m_min, m_max;

	static constexpr T INFT = INF<T>;
	Interval() : m_min(+INFT), m_max(-INFT){} // default interval is empty

	Interval(T min, T max) : m_min(min), m_max(max) {}

	Interval(const Interval& a, const Interval& b)
	{
		m_min = a.m_min <= b.m_min ? a.m_min : b.m_min;
		m_max = a.m_max >= b.m_max ? a.m_max : b.m_max;
	}

	T size() { return m_max - m_min; }

	bool contains(T x) const
	{
		return (x >= m_min && x <= m_max);
	}

	bool surrounds(T x) const
	{
		return (x > m_min && x < m_max);
	}

	T clamp(T val) const
	{
		if (val < m_min) return m_min;
		if (val > m_max) return m_max;
		return val;
	}

	Interval expand(T delta)
	{
		auto padding = delta / 2;
		return Interval(m_min - padding, m_max + padding);
	}
	
	static const Interval<T> empty;
	static const Interval<T> universe;
};

template<typename T>
const Interval<T> Interval<T>::empty{ +Interval<T>::INFT,
									  -Interval<T>::INFT };

template<typename T>
const Interval<T> Interval<T>::universe{ -Interval<T>::INFT,
										 +Interval<T>::INFT };

using IntervalF = Interval<float>;