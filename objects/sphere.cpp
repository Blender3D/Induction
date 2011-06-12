#include <math.h>
#include <stdlib.h>

class Sphere: public BaseObject {
  public:
    float radius;
    
    float intersection(Ray ray) {
      Vector distance = ray.origin - position;
      float b = distance.dot(ray.direction);
      float c = distance.dot(distance) - radius*radius;
      float d = b*b - c;
      
      if (d > 0.0) {
        float solution1 = -b - sqrt(d);
        float solution2 = -b + sqrt(d);
        
        if (solution1 > solution2) {
          return solution2;
        } else {
          return solution1;
        }
      } else {
        return false;
      }
    }

    Vector getNormal(Point positionition) {
      return (positionition - position).norm();
    }
};
