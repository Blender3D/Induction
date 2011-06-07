#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct Vector {
  double x, y, z;
  
  Vector(double _x = 0, double _y = 0, double _z = 0) {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
  }
  
  Vector operator-(const Vector &other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
  }
  
  Vector operator*(double other) const {
    return Vector(x * other, y * other, z * other);
  }
  
  Vector norm() {
    return *this * (1 / sqrt(x*x + y*y + z*z));
  }
  
  double dot(const Vector &other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  
  Vector cross(const Vector &other) const {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  }
};

main() {
  
}
