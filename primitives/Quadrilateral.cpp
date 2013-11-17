#include "Quadrilateral.h"

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Primitive.h"

#include <cmath>

float Quadrilateral::getIntersection(Ray *ray) const {
	Vector edge_12 = point2 - point1;
	Vector edge_14 = point4 - point1;
	Vector P = ray->direction.cross(edge_14);

	float determinant = edge_12.dot(P);

	if (abs(determinant) < epsilon) {
		return false;
	}

	Vector T = ray->origin - point1;

	float inverse_determinant = 1.0 / determinant;
	float alpha = T.dot(P) * inverse_determinant;

	if ((alpha < 0.0) || (alpha > 1.0)) {
		return false;
	}

	Vector Q = T.cross(edge_12);
	float beta = ray->direction.dot(Q) * inverse_determinant;

	if ((beta < 0.0) || (beta > 1.0)) {
		return false; 
	}

	if ((alpha + beta) > 1.0) {
		Vector edge_34 = point4 - point3;
		Vector edge_32 = point2 - point3;
		Vector P_prime = ray->direction.cross(edge_32);
		float determinant_prime = edge_34.dot(P_prime);

		if (abs(determinant_prime) < epsilon) {
			return false;
		}

		float inverse_determinant_prime = 1.0 / determinant_prime;
		Vector T_prime = ray->origin - point3;
		float alpha_prime = T_prime.dot(P_prime) * inverse_determinant_prime;

		if (alpha_prime < 0.0) {
			return false;
		}

		Vector Q_prime = T_prime.cross(edge_34);
		float beta_prime = ray->direction.dot(Q_prime) * inverse_determinant_prime;

		if (beta_prime < 0.0) {
			return false;
		}
	}

	float t = edge_14.dot(Q) * inverse_determinant;

	if (t < 0.0) {
		return false;
	}

	return t;
}

float Quadrilateral::getSurfaceArea() const {
	return 0.5 * ((point1 - point2).cross(point1 - point4).length() + (point3 - point2).cross(point3 - point4).length());
}

float Quadrilateral::getVolume() const {
	return 0;
}

void Quadrilateral::createBoundingBox() const {
	box.corner1 = Point(
		min(min(point1.x, point2.x), min(point3.x, point4.x)),
		min(min(point1.y, point2.y), min(point3.y, point4.y)), 
		min(min(point1.z, point2.z), min(point3.z, point4.z))
	);

	box.corner2 = Point(
		max(max(point1.x, point2.x), max(point3.x, point4.x)),
		max(max(point1.y, point2.y), max(point3.y, point4.y)), 
		max(max(point1.z, point2.z), max(point3.z, point4.z))
	);
}

Vector Quadrilateral::getNormal(Point *point) const {
	return normal;
}

Point Quadrilateral::getLightSample() const {
	float r1 = random_uniform();
	float r2 = (1 - r1) * random_uniform();
	float r3 = 1 - r1 - r2;

	if (random_uniform() > 0.5) {
		return point1 * r1 + point2 * r2 + point3 * r3;
	} else {
		return point3 * r1 + point4 * r2 + point1 * r3;
	}
}
