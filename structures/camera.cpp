#include <math.h>

#include "ray.h"
#include "camera.h"

Camera::Camera() {
  
}

void Camera::setSize(float _width, float _height) {
  width = _width;
  height = _height;
}

void Camera::setPixelDensity(float density) {
  canvasWidth = (int)(width * density);
  canvasHeight = (int)(height * density);
  
  cX = width / canvasWidth;
  cY = height / canvasHeight;
}

void Camera::setFocus(Point focus) {
  direction = (position - focus).norm();
}

void Camera::setSamples(int _samples) {
  samples = _samples;
}

Ray Camera::castRay(float x, float y) {
  return Ray(position, Vector(x * cX - width / 2.0, 1, y * cY - height / 2.0));
}
