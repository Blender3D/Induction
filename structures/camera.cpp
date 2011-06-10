#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct Camera {
  Point pos;
  Vector dir;
  ViewPlane viewplane;
  float cX, cY;
  
  Camera(Point _pos, Point _focus, ViewPlane _viewplane) {
    pos = _pos;
    dir = (_pos - _focus).norm();
    viewplane = _viewplane;
    cX = _viewplane.width / _viewplane.canvasWidth;
    cY = _viewplane.height / _viewplane.canvasHeight;
  }
  
  Ray CastRay(float x, float y) {
    return Ray(pos, Vector(x * cX - viewplane.width / 2.0, 1.0, y * cY - viewplane.height / 2.0));
  }
};
