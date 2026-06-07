#include "Vector.h"

float crossProduct2D(Vector2f v1, Vector2f v2)
{
	return v1[X] * v2[Y] - v2[X] * v1[Y];
}

Vector3f crossProduct3D(Vector3f v1, Vector3f v2)
{
	float x, y, z;

	x = v1[Y] * v2[Z] - v1[Z] * v2[Y];
	y = -(v1[X] * v2[Z] - v1[Z] * v2[X]);
	z = v1[X] * v2[Y] - v1[Y] * v2[X];

	return Vector3f(x, y, z);
}

/*used in calculation of tetrahedron volume. volume of tetrahedron is 1/6 of the scalar triple product.*/
float scalarTripleProduct(Vector3f v1, Vector3f v2, Vector3f v3)
{
	return v1.dot(crossProduct3D(v2, v3));
}