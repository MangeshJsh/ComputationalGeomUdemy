#include "Color.h"
#include "Interval.h"

float linearToGamma(float linearComponent)
{
	if (linearComponent > 0.0)
		return std::sqrt(linearComponent);

	return 0.0;
}

void write_color(std::ostream& out, const Color& pixelColor)
{
	auto r = pixelColor[X];
	auto g = pixelColor[Y];
	auto b = pixelColor[Z];

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	static const IntervalF intensity{ 0.000, 0.999 };
	auto rbyte = static_cast<int>(256 * intensity.clamp(r));
	auto gbyte = static_cast<int>(256 * intensity.clamp(g));
	auto bbyte = static_cast<int>(256 * intensity.clamp(b));

	out << rbyte << " " << gbyte << " " << bbyte << '\n';
}