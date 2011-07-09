#include <cmath>
#include <stdlib.h>

float random_uniform() {
  return ((float)rand()) / RAND_MAX;
}

int random_int(int end) {
  return ((float)rand() * (end - 1)) / RAND_MAX;
}

Vector uniform_hemisphere(Vector normal = Vector(0, 0, 0)) {
  float random = random_uniform();
  float radius = sqrt(1 - random * random);
  float phi = TWO_PI * random_uniform();
  Vector vector = Vector(radius * cos(phi), radius * sin(phi), random);
  
  return (normal == Vector(0, 0, 0)) ? vector : vector * (2 * (vector.dot(normal) < 0.0) - 1);
}

float uniform_hemisphere_pdf(float theta, float phi) {
  return INV_TWO_PI;
}

Vector cosine_weighted_hemisphere(Vector normal) {
  float theta = acos(sqrt(random_uniform()));
  float phi = TWO_PI * random_uniform();

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

float cosine_weighted_hemisphere_pdf(float theta, float phi) {
  return (cos(theta) * sin(theta)) * INV_PI;
}