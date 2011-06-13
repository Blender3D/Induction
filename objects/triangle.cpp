#include <cmath>
#include <stdlib.h>

class Triangle: public BaseObject {
  public:
    Point point1, point2, point3, point4;

    float intersection(Ray ray) {
      Vector u = point2 - point1;
      Vector v = point3 - point1;
      Vector normal = u.cross(v);

      Vector w0 = ray.origin - point1;
      float a = -normal.dot(w0);
      float b = normal.dot(ray.direction);

      if (abs(b) < 0.0000001) {
        return false;
      }

      float ratio = a / b;

      if (ratio < 0.0) {
        return false;
      }

      Point intersect = ray.position(ratio);

      float uu = u.abs();
      float uv = u.dot(v);
      float vv = v.abs();
      Vector w = intersect - point1;
      float wu = w.dot(u);
      float wv = w.dot(v);
      float D = uv * uv - uu * vv;

      float s = (uv * wv - vv * wu) / D;

      if (s < 0.0 || s > 1.0) {
        return false;
      }

      float t = (uv * wu - uu * wv) / D;

      if (t < 0.0 || (s + t) > 1.0) {
        return false;
      }

      return t;
    }
      
    Vector getNormal(Point _position) {
      return (point2 - point1).cross(point3 - point2);
    }
};
