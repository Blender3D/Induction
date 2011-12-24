#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include "ray.h"

class Camera {
  public:
    Point position;
    Vector direction;
    float cX, cY;
    float pixelDensity, offset, width, height;
    int canvasWidth, canvasHeight;
    int samples;
    
    ~Camera() {};

    Camera();
    
    void setSize(float, float);
    void setPixelDensity(float);
    void setFocus(Point);
    void setSamples(int);
    
    Ray castRay(float, float);
};

#endif
