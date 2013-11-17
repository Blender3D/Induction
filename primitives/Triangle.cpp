#include "Triangle.h"

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

#include <cmath>

Triangle::Triangle() : point1(Point()), point2(Point()), point3(Point()) {
	createBoundingBox();
	computeNormal();
}

Triangle::Triangle(Point point1, Point point2, Point point3) : point1(point1), point2(point2), point3(point3) {
	createBoundingBox();
	computeNormal();
}

Triangle::~Triangle() {

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

float Triangle::getSurfaceArea() const {
	return 0.5 * normal.length();
}

float Triangle::getVolume() const {
	return 0;
}

void Triangle::createBoundingBox() {
	boundingBox.corner1 = Point(
		min(min(point1.x, point2.x), point3.x), 
		min(min(point1.y, point2.y), point3.y), 
		min(min(point1.z, point2.z), point3.z)
	);

	boundingBox.corner2 = Point(
		max(max(point1.x, point2.x), point3.x), 
		max(max(point1.y, point2.y), point3.y), 
		max(max(point1.z, point2.z), point3.z)
	);
}

Vector Triangle::getNormal(Point *point) const {
	return normal;
}

Point Triangle::getLightSample() const {
	float r1 = random_uniform();
	float r2 = (1 - r1) * random_uniform();
	float r3 = 1 - r1 - r2;

	return point1 * r1  + point2 * r2 + point3 * r3;
}

void Triangle::setPoint1(Point point1) const {
	point1 = point1;
	createBoundingBox();
	computeNormal();
}

void Triangle::setPoint2(Point point2) const {
	point2 = point2;
	createBoundingBox();
	computeNormal();
}

void Triangle::setPoint1(Point point3) const {
	point3 = point3;
	createBoundingBox();
	computeNormal();
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
