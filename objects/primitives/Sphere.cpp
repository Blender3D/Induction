#include "Sphere.h"

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"

#include "constants.h"

#include <cmath>

Sphere::Sphere() : radius(0) {
	createBoundingBox();
}

Sphere::Sphere(float radius) : radius(radius) {
	createBoundingBox();
}

float Sphere::getIntersection(Ray *ray) const {
	Vector distance = ray->origin - position;
	float b = distance.dot(ray->direction);
	float c = distance.dot(distance) - radius*radius;
	float d = b*b - c;

	if (d <= 0.0) {
		return false;
	}

	float solution1 = -b - sqrt(d);
	float solution2 = -b + sqrt(d);

	if (solution1 > solution2) {
		return solution2;
	} else {
		return solution1;
	}
}

void Sphere::setRadius(float r) {
	radius = r;
	createBoundingBox();
}

float Sphere::getRadius() const {
	return radius;
}

Vector Sphere::getNormal(Point *point) const {
	return (position - *point).norm();
}
