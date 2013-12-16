#include "primitives/Sphere.h"

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"

#include <cmath>

Sphere::Sphere() : radius(0) {}

Sphere::Sphere(float radius) : radius(radius) {}

bool Sphere::intersects(const Ray &ray) const {
	Vector distance = ray.origin - position;

	float b = distance.dot(ray.direction);
	float c = distance.dot(distance) - radius*radius;
	float d = b*b - c;

	return d > 0;
}

float Sphere::getIntersection(const Ray &ray) const {
	Vector distance = ray.origin - position;

	float negative_b = -distance.dot(ray.direction);
	float b_squared = negative_b * negative_b;

	float c = distance.dot(distance) - radius*radius;
	float d = b_squared - c;

	if (d > b_squared) {
		return negative_b + std::sqrt(d);
	} else {
		return negative_b - std::sqrt(d);
	}
}

Vector Sphere::getNormal(const Point &point) const {
	return (position - point).norm();
}
