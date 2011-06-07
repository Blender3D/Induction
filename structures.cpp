#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define MAXWIDTH 2000
#define MAXHEIGHT 2000

using namespace std;

struct Vector {
  float x, y, z;
  
  Vector(float _x = 0, float _y = 0, float _z = 0) {
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
  
  Vector operator*(float other) const {
    return Vector(x * other, y * other, z * other);
  }
  
  Vector operator*(Vector other) const {
    return Vector(x * other.x, y * other.y, z * other.z);
  }
  
  Vector operator/(float other) const {
    return *this * (1 / other);
  }
  
  Vector norm() {
    return *this * (1 / sqrt(x*x + y*y + z*z));
  }
  
  float dot(const Vector &other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  
  Vector cross(const Vector &other) const {
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
  }
  
  float abs() {
    return sqrt(x*x + y*y + z*z);
  }
};

struct Ray {
  Vector origin;
  Vector direction;
  
  Ray(Vector _origin, Vector _direction) {
    origin = _origin;
    direction = _direction.norm();
  }
  
  Vector position(float &time) const {
    return origin + direction * time;
  }
};

struct ViewPlane {
  float pixelDensity, offset, width, height, canvasWidth, canvasHeight;
  
  ViewPlane(float _offset = 0, float _width = 0, float _height = 0, float _pixelDensity = 0) {
    pixelDensity = _pixelDensity;
    offset = _offset;
    width = _width;
    height = _height;
    canvasWidth = (int)(_width * _pixelDensity);
    canvasHeight = (int)(_height * _pixelDensity);
  }
};

struct Camera {
  Vector pos;
  Vector dir;
  ViewPlane viewplane;
  float cX, cY;
  
  Camera(Vector _pos, Vector _dir, ViewPlane _viewplane) {
    pos = _pos;
    dir = _dir;
    viewplane = _viewplane;
    cX = _viewplane.width / _viewplane.canvasWidth;
    cY = _viewplane.height / _viewplane.canvasHeight;
  }
  
  Ray CastRay(int x, int y) {
    return Ray(pos, Vector(x * cX - viewplane.width / 2, 1, y * cY - viewplane.height / 2));
  }
};

inline Vector Clamp(Vector &color) {
  if (color.x > 1)  color.x = 1;
  if (color.y > 1)  color.y = 1;
  if (color.z > 1)  color.z = 1;
  
  return color;
}

float random_uniform() {
  return ((float)rand()) / RAND_MAX;
}

inline Vector RandomNormalInHemisphere(Vector &v) {
  Vector v2 = Vector(2 * random_uniform() - 1, 2 * random_uniform() - 1, 2 * random_uniform() - 1).norm();

  while (v2.dot(v2) > 1) {
    v2 = Vector(2 * random_uniform() - 1, 2 * random_uniform() - 1, 2 * random_uniform() - 1).norm();
  }
  
  return v2 * (v2.dot(v) < 0);
}
