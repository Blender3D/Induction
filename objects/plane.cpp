#include <math.h>
#include <stdlib.h>

class Plane: public Object {
  public:
    Vector point1, point2;
    Vector normal;

    float intersection(Ray ray) {
      float k, t, test1, test2;
      Vector point;
      Vector toPoint;
      
      k = ray.direction.dot(normal);

      if (k != 0.0) {
        t = (pos - ray.origin).dot(normal) / k;
      } else {
        return false;
      }
      
      if (t < 0.0000001) {
        return false;
      }
      
      point = ray.position(t);
      toPoint = point - pos;
      
      test1 = toPoint.dot(point1);
      
      if (test1 < 0.0 || test1 > (point1 - pos).abs()) {
        return false;
      }
      
      test2 = toPoint.dot(point2);
      
      if (test2 < 0.0 || test2 > (point2 - pos).abs()) {
        return false;
      }
      
      return t;
    }
      
    Vector getNormal(Vector position) {
      return normal;
    }
};