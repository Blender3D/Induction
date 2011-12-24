#include <math.h>

#include "boundingbox.h"

using namespace std;

BoundingBox::BoundingBox() {

}

float BoundingBox::getIntersection(Ray ray) {
  float t0 = 0;
  float t1 = INFINITY;
  
  for (int i = 0; i < 3; ++i) {
    float invRayDir = 1 / ray.direction[i];
    cout << corner1[i] << endl;
    float tNear = (corner1[i] - ray.origin[i]) * invRayDir;
    float tFar = (corner2[i] - ray.origin[i]) * invRayDir;
    
    if (tNear > tFar) {
      swap(tNear, tFar);
    }
    
    t0 = tNear > t0 ? tNear : t0;
    t1 = tFar < t1 ? tFar : t1;
    
    if (t0 > t1) {
      return false;
    }
  }
  
  return true;
}
