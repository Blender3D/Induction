#include <cmath>
#include <stdlib.h>

class Triangle: public BaseObject {
  public:
    Point point1, point2, point3;
    Vector normal;

    float intersection(Ray ray) {
      Vector u = point2 - point1;
      Vector v = point3 - point1;
      Vector n = u.cross(v);

      Vector w0 = ray.origin - point1;
      float a = -n.dot(w0);
      float b = n.dot(ray.direction);
      
      if (abs(b) < 0.0000001) {
        return false;
      }

      float ratio = a / b;
      
      if (ratio < 0) {
        return false;
      }

      Point intersection = ray.position(ratio);

      float uu = u.dot(u);
      float uv = u.dot(v);
      float vv = v.dot(v);
      Vector w  = intersection - point1;
      float wu = w.dot(u);
      float wv = w.dot(v);
      float D = uv * uv - uu * vv;

      float s = (uv * wv - vv * wu) / D;
      
      if ((s < 0) || (s > 1)) {
        return false;
      }
      
      float t = (uv * wu - uu * wv) / D;
      
      if ((t < 0) || ((s + t) > 1)) {
        return false;
      }

      return ratio;
    }
      
    Vector getNormal(Point _position) {
      return normal;
    }
};
