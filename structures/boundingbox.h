#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <math.h>

#include "point.h"
#include "ray.h"

class BoundingBox {
  public:
    Point corner1, corner2;
    
    ~BoundingBox() {};
    BoundingBox();
    
    float getIntersection(Ray);
};

#endif
