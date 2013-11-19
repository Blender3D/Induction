#include "Triangle.h"

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

#include <cmath>
#include <cassert>

Triangle::Triangle() : point1(Point()), point2(Point()), point3(Point()) {
	createBoundingBox();
	computeNormal();
}

Triangle::Triangle(Point point1, Point point2, Point point3) : point1(point1), point2(point2), point3(point3) {
	createBoundingBox();
	computeNormal();
}

void Triangle::computeNormal() {
	normal = point1.cross(point2).norm();
}

float Triangle::getIntersection(Ray *ray) const {
	Vector u = point2 - point1;
	Vector v = point3 - point1;

	Vector w0 = ray->origin - point1;
	float a = -normal.dot(w0);
	float b = normal.dot(ray->direction);

	if (abs(b) < epsilon) {
		return false;
	}

	float ratio = a / b;

	if (ratio < 0) {
		return false;
	}

	Point intersection = ray->position(ratio);
	Vector w  = intersection - point1;

	float uu = u.length();
	float uv = u.dot(v);
	float vv = v.length();
	float wu = w.dot(u);
	float wv = w.dot(v);
	float D = uv * uv - uu * vv;

	float s = (uv * wv - vv * wu) / D;

	if ((s < 0) || (s > 1)) {
		return false;
	}

	float t = (uv * wu - uu * wv) / D;

	if ((t < 0) || ((s + t) > 1)) {
		return false;
	}

	return ratio;
}

Vector Triangle::getNormal(Point *point) const {
	return normal;
}

void Triangle::setNormal(Vector *vector) {
	assert(vector->dot(point1.cross(point2)) == 0);

	normal = *vector;
}

void Triangle::setPoint1(Point point1) const {
	point1 = point1;
	computeNormal();
	createBoundingBox();
}

void Triangle::setPoint2(Point point2) const {
	point2 = point2;
	computeNormal();
	createBoundingBox();
}

void Triangle::setPoint1(Point point3) const {
	point3 = point3;
	computeNormal();
	createBoundingBox();
}

Point Triangle::getPoint1() const {
	return point1;
}

Point Triangle::getPoint2() const {
	return point2;
}

Point Triangle::getPoint1() const {
	return point3;
}
