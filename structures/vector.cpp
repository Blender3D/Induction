#include <math.h>

#include "vector.h"
#include "point.h"

using namespace std;

Vector::Vector() {
  x = 0;
  y = 0;
  z = 0;
}

Vector::Vector(Point point) {
  x = point.x;
  y = point.y;
  z = point.z;
}

Vector::Vector(float k) {
  x = k;
  y = k;
  z = k;
}

Vector::Vector(float _x, float _y) {
  x = _x;
  y = _y;
}

Vector::Vector(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

Vector Vector::operator+(Vector vector) {
  return Vector(x + vector.x, y + vector.y, z + vector.z);
}

Point Vector::operator+(Point point) {
  return Point(x + point.x, y + point.y, z + point.z);
}

Point Vector::operator-(Point point) {
  return Point(x - point.x, y - point.y, z - point.z);
}

Vector Vector::operator-(Vector vector) {
  return Vector(vector.x - x, vector.y - y, vector.z - z);
}

Vector Vector::operator*(float k) {
  return Vector(x * k, y * k, z * k);
}

Vector Vector::operator/(float k) {
  return Vector(x / k, y / k, z / k);
}

bool Vector::operator==(Vector other) {
  return ((x == other.x) && (y == other.y) && (z == other.z));
}

bool Vector::operator!=(Vector other) {
  return ((x != other.x) || (y != other.y) || (z != other.z));
}

ostream& operator<<(ostream& stream, Vector& vector) {
  stream << "Point(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  
  return stream;
}

float Vector::operator[](int index) {
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

float Vector::length() {
  return sqrt(dot(*this));
}

Vector Vector::norm() {
  return *this * (1.0 / length());
}

float Vector::dot(Vector other) {
  return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(Vector other) {
  return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}
