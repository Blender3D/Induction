#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

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
