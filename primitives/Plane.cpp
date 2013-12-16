#include "Plane.h"

#include "objects/Point.h"
#include "objects/Vector.h"
#include "objects/Ray.h"

#include "constants.h"

Plane::Plane() : normal(Vector()) {}

Plane::Plane(Vector normal) : normal(normal) {}

float Plane::getIntersection(Ray *ray) const {
	float k = ray->direction.dot(normal);

	if (k == 0.0) {
		return false;
	}

	float t = (position - ray->origin).dot(normal) / k;

	if (t < EPSILON) {
		return false;
	}

	return t;
}

float Plane::intersects(Ray *ray) const {
	return getIntersection(ray) > 0;
}
