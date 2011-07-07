#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct Vector {
  float x, y, z;
  
  Vector(float _x = 0.0, float _y = 0.0, float _z = 0.0) {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Vector operator +(Vector other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
  }
  
  Vector operator +(float other) const {
    return Vector(x + other, y + other, z + other);
  }
  
  Vector operator -(Vector other) const {
    return Vector(x - other.x, y - other.y, z - other.z);
  }
  
  Vector operator *(float other) const {
    return Vector(x * other, y * other, z * other);
  }
  
  Vector operator *(Vector other) const {
    return Vector(x * other.x, y * other.y, z * other.z);
  }
  
  Vector operator /(float other) const {
    return *this * (1.0 / other);
  }
  
  bool operator ==(Vector other) {
    return ((other.x == x) && (other.y == y) && (other.z == z));
  }
  
  bool operator !=(Vector other) {
    return ((other.x != x) || (other.y != y) || (other.z == z));
  }
  
  bool operator >(Vector other) {
    return ((other.x > x) && (other.y > y) && (other.z > z));
  }
  
  bool operator >=(Vector other) {
    return ((other.x >= x) && (other.y >= y) && (other.z >= z));
  }
  
  bool operator <(Vector other) {
    return ((other.x < x) && (other.y < y) && (other.z < z));
  }
  
  bool operator <=(Vector other) {
    return ((other.x <= x) && (other.y <= y) && (other.z <= z));
  }
  
  Vector operator +=(Vector other) {
    *this = *this + other;
    return *this;
  }
  
  Vector operator +=(float other) {
    *this = *this + other;
    return *this;
  }
  
  Vector operator -=(Vector other) {
    *this = *this - other;
    return *this;
  }
  
  Vector operator -=(float other) {
    *this = *this - other;
    return *this;
  }
  
  Vector operator *=(Vector other) {
    *this = *this * other;
    return *this;
  }
  
  Vector operator *=(float other) {
    *this = *this * other;
    return *this;
  }
  
  Vector operator /=(float other) {
    *this = *this / other;
    return *this;
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
  
  Vector norm() {
    return *this * (1.0 / sqrt(x*x + y*y + z*z));
  }
  
  float dot(Vector other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  
  Vector cross(Vector other) const {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  }
  
  float abs() {
    return sqrt(x*x + y*y + z*z);
  }
};
