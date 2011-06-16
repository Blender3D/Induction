#include <cmath>
#include <stdlib.h>

float random_uniform() {
  return ((float)rand()) / RAND_MAX;
}

int random_int(int end) {
  return ((float)rand() * (end - 1)) / RAND_MAX;
}

Vector random_vector(Vector normal = Vector(0, 0, 0)) {
  Vector v2;
  
  do {
    v2 = Vector(2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0).norm();
  } while (v2.abs() > 1.0);

  return (normal == Vector(0, 0, 0)) ? v2 : v2 * (2 * (v2.dot(normal) < 0.0) - 1);
}

Vector cosine_weighted_random_vector(Vector normal) {
  float theta = acos(sqrt(random_uniform()));
  float phi = 2.0 * 3.1415926535897932384626433832795 * random_uniform();

  Vector result = normal;
  
  if ((abs(result.x) <= fabs(result.y)) && (abs(result.x) <= fabs(result.z))) {
    result.x = 1;
  } else if ((abs(result.y) <= abs(result.x)) && (abs(result.y) <= fabs(result.z))) {
    result.y = 1;
  } else {
    result.z = 1;
  }
  
  Vector x = (result.cross(normal)).norm();
  Vector z = (x.cross(normal)).norm();

  return (x * sin(theta) * cos(phi) + normal * cos(theta) + z * sin(theta) * sin(phi)).norm() * -1;
}
