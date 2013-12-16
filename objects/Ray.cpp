#include "objects/Ray.h"

#include "objects/Vector.h"
#include "objects/Point.h"

Ray::Ray() : origin(Point()), direction(Vector()) {}

Ray::Ray(const Point &origin, const Vector &direction):
  origin(origin), direction(direction) {}

Point Ray::position(float distance) {
	return origin + direction * distance;
}

inline bool Ray::operator==(const Ray &other) {
	return (origin == other.origin) && (direction == other.direction);
}
