#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define MAXWIDTH 2000
#define MAXHEIGHT 2000

using namespace std;

struct Vector {
  float x, y, z;
  
  Vector(float _x = 0.0, float _y = 0.0, float _z = 0.0) {
    x = _x;
    y = _y;
    z = _z;
  }
  
  Vector operator+(const Vector &other) const {
    return Vector(x + other.x, y + other.y, z + other.z);
  }
  
  Vector operator+(float other) const {
    return Vector(x + other, y + other, z + other);
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
    return *this * (1.0 / other);
  }
  
  Vector norm() {
    return *this * (1.0 / sqrt(x*x + y*y + z*z));
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
  
  ViewPlane(float _offset = 0.0, float _width = 0.0, float _height = 0.0, float _pixelDensity = 0.0) {
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
    dir = _dir.norm();
    viewplane = _viewplane;
    cX = _viewplane.width / _viewplane.canvasWidth;
    cY = _viewplane.height / _viewplane.canvasHeight;
  }
  
  Ray CastRay(float x, float y) {
    return Ray(pos, Vector(x * cX - viewplane.width / 2.0, 1.0, y * cY - viewplane.height / 2.0));
  }
};

inline Vector Clamp(Vector color) {
  if (color.x > 1.0)  color.x = 1.0;
  if (color.y > 1.0)  color.y = 1.0;
  if (color.z > 1.0)  color.z = 1.0;
  
  return color;
}

float random_uniform() {
  return ((float)rand()) / RAND_MAX;
}

inline Vector RandomNormalInHemisphere(Vector v) {
  Vector v2 = Vector(2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0).norm();

  while (v2.dot(v2) > 1.0) {
    v2 = Vector(2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0).norm();
  }
  
  return v2 * (2 * (v2.dot(v) < 0.0) - 1);
}
