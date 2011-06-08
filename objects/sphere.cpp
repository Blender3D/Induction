#include <math.h>
#include <stdlib.h>

class Sphere: public Object {
  public:
    float emittance;
    Vector diffuse;
    float radius;
    
    float intersection(Ray ray) {
      Vector distance;
      float b, c, d;
      
      distance = ray.origin - pos;
      b = distance.dot(ray.direction);
      c = distance.dot(distance) - radius*radius;
      d = b*b - c;
      
      if (d > 0.0) {
        return -b - sqrt(d);
      } else {
        return false;
      }
    }

    Vector getNormal(Vector position) {
      return (position - pos).norm();
    }
};