#include <math.h>
#include <stdlib.h>

float random_uniform() {
  return ((float)rand()) / RAND_MAX;
}

Vector random_vector(Vector normal = Vector(0, 0, 0)) {
  Vector v2;
  
  do {
    v2 = Vector(2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0).norm();
  } while (v2.abs() > 1.0);

  return (normal == Vector(0, 0, 0)) ? v2 : v2 * (2 * (v2.dot(normal) < 0.0) - 1);
}