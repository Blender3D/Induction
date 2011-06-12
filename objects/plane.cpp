#include <math.h>
#include <stdlib.h>

class Plane: public BaseObject {
  public:
    Vector normal;

    float intersection(Ray ray) {
      float k, t;
      Point point;
      Vector toPoint;
      
      k = ray.direction.dot(normal);

      if (k != 0.0) {
        t = (position - ray.origin).dot(normal) / k;
      } else {
        return false;
      }
      
      if (t < 0.0000001) {
        return false;
      }
      
      return t;
    }
      
    Vector getNormal(Point positionition) {
      return normal;
    }
};
