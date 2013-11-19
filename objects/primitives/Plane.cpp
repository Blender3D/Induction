#include "Plane.h"

#include "Point.h"
#include "Vector.h"
#include "Ray.h"

#include "constants.h"

#include <cmath>

Plane::Plane() : normal(Vector()) {
	createBoundingBox();
}

Plane::Plane(Vector normal) : normal(normal) {
	createBoundingBox();
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

Vector Plane::getNormal(Point *point) const {
	return normal;
}

void Plane::setNormal(Vector *vector) const {
	normal = *vector;
}
