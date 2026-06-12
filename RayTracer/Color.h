#pragma once

#include "Vector.h"

using color = Vector3f;

void write_color(std::ostream& out, const color& pixelColor)
{
	//convert values in the range 0-1 to 0 to 255
	auto rbyte = static_cast<int>(255.999 * pixelColor[X]);
	auto gbyte = static_cast<int>(255.999 * pixelColor[Y]);
	auto bbyte = static_cast<int>(255.999 * pixelColor[Z]);

	out << rbyte << " " << gbyte << " " << bbyte << '\n';
}