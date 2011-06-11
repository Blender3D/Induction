#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Camera {
  public:
    Point pos;
    Vector dir;
    float cX, cY;
    float pixelDensity, offset, width, height;
    int canvasWidth, canvasHeight;
    
    void setSize(float _width, float _height) {
      width = _width;
      height = _height;
    }
    
    void setPixelDensity(float density) {
      canvasWidth = (int)(width * density);
      canvasHeight = (int)(height * density);
      
      cX = width / canvasWidth;
      cY = height / canvasHeight;
    }
    
    void setFocus(Point focus) {
      dir = (pos - focus).norm();
    }
    
    Ray CastRay(float x, float y) {
      return Ray(pos, Vector(x * cX - width / 2.0, 1.0, y * cY - height / 2.0));
    }
};
