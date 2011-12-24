#ifndef SAMPLER_H
#define SAMPLER_H

#include <math.h>
#include <vector>

#include "../structures/point.h"

class Sampler {
  public:
    std::vector<Point> coordinates;
    int width, height;
    
    ~Sampler() {};
    Sampler();
    
    virtual void init() = 0;
    Point getPixel(int, int);
};

#endif
