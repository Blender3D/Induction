#include "Triangle.h"

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"
#include "primitives/Primitive.h"

#include <cmath>

void Triangle::computeNormal() {
	normal = point1.cross(point2).norm();
}

Triangle::Triangle() : point1(Point()), point2(Point()), point3(Point()) {
	computeNormal();
}

Triangle::Triangle(const Point &point1, const Point &point2, const Point &point3) : 
  point1(point1), point2(point2), point3(point3) {
	computeNormal();
}

float Triangle::getIntersection(const Ray &ray) const {
	Vector u = point2 - point1;
	Vector v = point3 - point1;

	Vector w0 = ray.origin - point1;
	float a = -normal.dot(w0);
	float b = normal.dot(ray.direction);

	if (abs(b) < epsilon) {
		return false;
	}

	float ratio = a / b;

	if (ratio < 0) {
		return false;
	}

	Point intersection = ray.position(ratio);
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

bool Triangle::intersects(const Ray &ray) const {
	return getIntersection(ray) > 0;
}

Vector Triangle::getNormal(const Point &point) const {
	return normal;
}
