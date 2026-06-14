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

	T size() { return m_max - m_min; }

	bool contains(T x) const
	{
		return (x >= m_min && x <= m_max);
	}

	bool surrounds(T x) const
	{
		return (x > m_min && x < m_max);
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