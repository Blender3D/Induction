#include <math.h>

#include "point.h"

using namespace std;

Point::Point() {
  x = 0;
  y = 0;
  z = 0;
}

Point::Point(Vector vector) {
  x = vector.x;
  y = vector.y;
  z = vector.z;
}

Point::Point(float k) {
  x = k;
  y = k;
  z = k;
}

Point::Point(float _x, float _y) {
  x = _x;
  y = _y;
}

Point::Point(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

Point Point::operator+(Vector vector) {
  return Point(x + vector.x, y + vector.y, z + vector.z);
}

Point Point::operator+(Point point) {
  return Point(x + point.x, y + point.y, z + point.z);
}

Vector Point::operator-(Point point) {
  return Vector(x - point.x, y - point.y, z - point.z);
}

Point Point::operator*(float k) {
  return Point(x * k, y * k, z * k);
}

Point Point::operator/(float k) {
  return Point(x / k, y / k, z / k);
}

bool Point::operator==(Point other) {
  return ((x == other.x) && (y == other.y) && (z == other.z));
}

bool Point::operator!=(Point other) {
  return ((x != other.x) || (y != other.y) || (z != other.z));
}

bool Point::operator>(Point other) {
  return ((x > other.x) && (y > other.y) && (z > other.z));
}

bool Point::operator<(Point other) {
  return ((x < other.x) && (y < other.y) && (z < other.z));
}

float Point::distanceFrom(Point other) {
  return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

ostream& operator<<(ostream& stream, Point& point) {
  stream << "Point(" << point.x << ", " << point.y << ", " << point.z << ")";
  
  return stream;
}

float Point::operator[](int index) {
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
