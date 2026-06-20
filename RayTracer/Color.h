#pragma once

#include "Vector.h"

using Color = Vector3f;

float linearToGamma(float linearComponent);

void write_color(std::ostream& out, const Color& pixelColor);