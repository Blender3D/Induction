#include <math.h>
#include <stdlib.h>

struct Point {
  float x, y, z;
  
  Point(float _x = 0, float _y = 0, float _z = 0) {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Point operator+(const Point &other) const {
    return Point(x + other.x, y + other.y, z + other.z);
  }
  
  Point operator+(const Vector &other) const {
    return Point(x + other.x, y + other.y, z + other.z);
  }

  Vector operator-(const Point &other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
  }
};
