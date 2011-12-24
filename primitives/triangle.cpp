#include <math.h>
#include <stdlib.h>

class Triangle: public Primitive {
  public:
    Point point1, point2, point3;
    Vector normal;

    float getIntersection(Ray ray) {
      Vector u = point2 - point1;
      Vector v = point3 - point1;
      Vector n = u.cross(v);

      Vector w0 = ray.origin - point1;
      float a = -n.dot(w0);
      float b = n.dot(ray.direction);
      
      if (fabs(b) < 0.0000001) {
        return false;
      }

      float ratio = a / b;
      
      if (ratio < 0) {
        return false;
      }

      Point getIntersection = ray.position(ratio);

      float uu = u.dot(u);
      float uv = u.dot(v);
      float vv = v.dot(v);
      Vector w  = getIntersection - point1;
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
    
    float getSurfaceArea() {
      return 0.5 * (point1 - point2).cross(point1 - point3).length();
    }
    
    float getVolume() {
      return 0;
    }
    
    BoundingBox* createBoundingBox() {
      BoundingBox* box = new BoundingBox();
      
      box->corner1 = Point(min(min(point1.x, point2.x), point3.x), 
                           min(min(point1.y, point2.y), point3.y), 
                           min(min(point1.z, point2.z), point3.z));
      
      box->corner2 = Point(max(max(point1.x, point2.x), point3.x), 
                           max(max(point1.y, point2.y), point3.y), 
                           max(max(point1.z, point2.z), point3.z));
      
      boundingBox = box;
      return box;
    }
      
    Vector getNormal(Point _position) {
      _position = _position;
      return normal;
    }
    
    Point getLightSample() {
      float r1 = random_uniform();
      float r2 = (1 - r1) * random_uniform();
      float r3 = 1 - r1 - r2;
      
      return point1 * r1  + point2 * r2 + point3 * r3;
    }
};
