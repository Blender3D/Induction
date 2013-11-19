#include <math.h>

#include "ray.h"

Ray::Ray() {
  origin = Point();
  direction = Vector();
}

Ray::Ray(Point _origin, Vector _direction) {
  origin = _origin;
  direction = _direction.norm();
}

Point Ray::position(float time) {
  return origin + direction * time;
}

bool operator==(Ray a, Ray b) {
  return ((a.origin == b.origin) && (a.direction == b.direction));
}
