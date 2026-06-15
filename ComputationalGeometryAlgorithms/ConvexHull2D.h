#pragma once

#include "Core.h"
#include "Point.h"
#include "GeoUtils.h"
#include <vector>
#include <algorithm>


void giftWrapping(const std::vector<Point2d>& points, std::vector<Point2d>& convex)
{
	if (points.size() < 3) return;

	//step 1 is to pick the point which is on the convex hull. This could be
	//left most, right most, top most or bottom most point

	Point2d bottomPoint = points[0];

	for (const auto& pt : points)
	{
		if ((pt[Y] < bottomPoint[Y]) ||
			(isEqualD(pt[Y],bottomPoint[Y]) && pt[X] < bottomPoint[X]))
		{
			bottomPoint = pt;
		}
	}

	//Find the second point of the convex hull by computing the point which forms 
	//minimum polar angle with the horizontal line passing through the first point

	Point2d minPolarPoint = points[0];
	double currentPolarAngle = 360;

	for (const auto& pt : points)
	{
		float polar_angle = polarAngle(pt, bottomPoint);

		if (pt != bottomPoint && currentPolarAngle > polar_angle)
		{
			minPolarPoint = pt;
			currentPolarAngle = polar_angle;
		}
	}

	convex.push_back(bottomPoint);
	convex.push_back(minPolarPoint);

	Point2d refPoint = minPolarPoint;
	int indexBeforeLast = 0;

	while (true)
	{
		currentPolarAngle = 360;
		for (size_t i = 0; i < points.size(); ++i)
		{
			Vector2f vec1 = refPoint - convex[indexBeforeLast];
			Vector2f vec2 = points[i] - refPoint;

			float angleBetween = angle(vec1, vec2);

			if (refPoint != points[i] && currentPolarAngle > angleBetween)
			{
				currentPolarAngle = angleBetween;
				minPolarPoint = points[i];
			}
		}

		if (minPolarPoint == bottomPoint) break;

		indexBeforeLast++;
		convex.push_back(minPolarPoint);
		refPoint = minPolarPoint;
	}
}

void modifiedGrahamScan(std::vector<Point2d>& points, std::vector<Point2d>& convex)
{
	if (points.size() < 3) return;

	std::sort(points.begin(), points.end(), [](const Point2d& a, const Point2d& b)
		{
			if (a[X] < b[X] || (a[X] == b[X] && a[Y] < b[Y]))
			{
				return true;
			}
			return false;
		});

	std::vector<Point2d> upper;
	std::vector<Point2d> lower;

	upper.push_back(*points.begin());
	upper.push_back(*(std::next(points.begin())));

	size_t index = 0;
	for (size_t i = 2; i < points.size(); ++i)
	{
		index = upper.size();
		const auto& nextPoint = points[i];
		while (upper.size() > 1 && left(upper[index - 2], upper[index - 1], nextPoint))
		{
			upper.pop_back();
			index = upper.size();
		}
		upper.push_back(nextPoint);
	}

	std::reverse(points.begin(), points.end());

	lower.push_back(*points.begin());
	lower.push_back(*(std::next(points.begin())));

	for (size_t i = 2; i < points.size(); ++i)
	{
		index = lower.size();
		const auto& nextPoint = points[i];
		while (lower.size() > 1 && left(lower[index - 2], lower[index - 1], nextPoint))
		{
			lower.pop_back();
			index = lower.size();
		}
		lower.push_back(nextPoint);
	}

	upper.pop_back();
	lower.pop_back();

	convex.insert(convex.end(), upper.begin(), upper.end());
	convex.insert(convex.end(), lower.begin(), lower.end());

}

