#include "Plane.h"

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"

#include <cmath>

Plane::Plane() : normal(Vector()) {
	createBoundingBox();
}

Plane::Plane(Vector normal) : normal(normal) {
	createBoundingBox();
}

Plane::~Plane() {

}

float Plane::getIntersection(Ray *ray) const {
	float t;
	float k = ray->direction.dot(normal);

	if (k == 0.0) {
		return false;
	}

	t = (position - ray->origin).dot(normal) / k;

	if (t < epsilon) {
		return false;
	}

	return t;
}

float Plane::getSurfaceArea() const {
	return INFINITY;
}

float Plane::getVolume() const {
	return 0;
}

Point Plane::getLightSample() const {
	Vector random;

	do {
		random = random_vector().cross(normal);
	} while (random == Vector(0, 0, 0));

	return random * radius * sqrt(random_uniform()) + position;
}

Vector Plane::getNormal(Point *point) {
	return normal;
}

void Plane::setNormal(Vector vector) {
	normal = vector;
}

void Plane::createBoundingBox() {}
