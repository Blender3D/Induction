#ifndef LIGHTPATH_H
#define LIGHTPATH_H

#include <vector>
#include <math.h>

using namespace std;

class HitPoint {
  public:
    int node;

    Vector normal;
    Vector input;
    Vector output;
};

class LightPath {
  public:
    vector<HitPoint> points;
};

#endif
