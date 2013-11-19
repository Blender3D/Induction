#ifndef LIGHTPATH_H
#define LIGHTPATH_H

#include <vector>
#include <math.h>

#include "vector.h"
#include "material.h"

using namespace std;

class HitPoint {
  public:
    int node;

    Vector normal;
    Vector input;
    Vector output;

    Material material;

    ~HitPoint() {};
    
    HitPoint();
    HitPoint(Vector, Vector, Vector, Material);
};

class LightPath {
  public:
    vector<HitPoint> points;

    ~LightPath() {};
    
    LightPath();

    void addPoint(HitPoint);
};

#endif
