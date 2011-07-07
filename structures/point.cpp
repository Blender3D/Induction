#include <math.h>
#include <stdlib.h>

struct Point {
  float x, y, z;
  
  Point(float _x = 0, float _y = 0, float _z = 0) {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Point operator +(Point other) const {
    return Point(x + other.x, y + other.y, z + other.z);
  }
  
  Point operator +(Vector other) const {
    return Point(x + other.x, y + other.y, z + other.z);
  }
  
  Point operator +(float other) const {
    return Point(x + other, y + other, z + other);
  }

  Vector operator -(Point other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
  }
  
  Point operator -(float other) const {
    return Point(x - other, y - other, z - other);
  }
  
  Point operator +=(Point other) {
    *this = *this + other;
    return *this;
  }
  
  bool operator ==(Point other) {
    return ((other.x == x) && (other.y == y) && (other.z == z));
  }
  
  bool operator !=(Point other) {
    return ((other.x != x) || (other.y != y) || (other.z == z));
  }
  
  bool operator >(Point other) {
    return ((other.x > x) && (other.y > y) && (other.z > z));
  }
  
  bool operator >=(Point other) {
    return ((other.x >= x) && (other.y >= y) && (other.z >= z));
  }
  
  bool operator <(Point other) {
    return ((other.x < x) && (other.y < y) && (other.z < z));
  }
  
  bool operator <=(Point other) {
    return ((other.x <= x) && (other.y <= y) && (other.z <= z));
  }
  
  float operator [](int index) {
    if (index == 0) {
      return x;
    } else if (index == 1) {
      return y;
    } else if (index == 2) {
      return z;
    } else {
      return 0;
    }
  }
};
