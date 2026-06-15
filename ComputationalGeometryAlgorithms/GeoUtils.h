#pragma once

#include "Core.h"
#include "Vector.h"
#include "Point.h"
#include "Line.h"
#include "Plane.h"
#include "Polygon.h"

double areaTriangle2D(const Point2d& a, const Point2d& b, const Point2d& c);

RelativePosition orientation2D(const Point2d& a, const Point2d& b, const Point2d& c);

bool isIntersecting(const Line<float, DIM2>& l1, const Line<float, DIM2>& l2);

bool isIntersecting(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d);

Point2d getIntersectionPoint(const Line<float, DIM2>& l1, const Line<float, DIM2>& l2);

Point2d getIntersectionPoint(const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d);

float angleBetweenLines2D(const Line<float, DIM2>& l1, const Line<float, DIM2>& l2);

float angleBetweenLines3D(const Line<float, DIM3>& l1, const Line<float, DIM3>& l2);

float angleBetweenLineAndPlane(const Line<float, DIM3>& l1, const Plane<float>& plane);

float angleBetweenTwoPlanes(const Plane<float>& plane1, const Plane<float>& plane2);

bool collinear( Vector3f v1,  Vector3f v2);

bool collinear(Point3d p1, Point3d p2, Point3d p3);

bool coplanar(Vector3f v1, Vector3f v2, Vector3f v3);

bool coplanar(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d);

float distantPointToLine(const Point3d& point, const Line<float, DIM3>& line);

float distance(const Point3d& p1, const Point3d& p2);

float distanceSquared(const Point3d& p1, const Point3d& p2);

float distancePointToPlane(const Point3d& p, const Plane<float>& plane);

bool intersectionPlaneAndPlane(const Plane<float>& plane1, const Plane<float>& plane2, Line<float, DIM3>& intersectionLine);

bool isDiagonal(const Vertex2d* v1, const Vertex2d* v2, PolygonS2d* poly = nullptr);

bool left(const Point2d& a, const Point2d& b, const Point2d& c);

bool leftOrBeyond(const Point2d& a, const Point2d& b, const Point2d& c);

// Returns counter clockwise angle (0 - 360) measure from referece point to the give point 
float polarAngle(const Point2d& _other, const Point2d& _ref);

float angle(const Vector2f& _v1, const Vector2f& _v2);