#ifndef RAY_H
#define RAY_H

#include <math.h>

#include "vector.h"
#include "point.h"

class Ray {
  public:
    Point origin;
    Vector direction;
    
    ~Ray() {}
    
    Ray();
    Ray(Point, Vector);
    
    Point position(float time);
    
    bool operator==(Ray);
};

#endif
