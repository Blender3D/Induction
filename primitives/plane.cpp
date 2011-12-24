#include <math.h>
#include <stdlib.h>

using namespace std;

class Plane: public Primitive {
  public:
    Vector normal;

    float getIntersection(Ray ray) {
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
    
    float getSurfaceArea() {
      return INFINITY;
    }
    
    float getVolume() {
      return 0;
    }
    
    Point getLightSample() {
      int max = 1000000;
      float u = max * (2 * random_uniform() - 1);
      float v = max * (2 * random_uniform() - 1);
      
      // Transform (u, v) coordinates to world (x, y, z) coordinates.

      return Point(u, v, 0);
    }
    
    BoundingBox* createBoundingBox() {
      BoundingBox* box = new BoundingBox();
      
      box->corner1 = Point(-INFINITY, -INFINITY, -INFINITY);
      box->corner2 = Point(INFINITY, INFINITY, INFINITY);
      
      boundingBox = box;
      return box;
    }
      
    Vector getNormal(Point _position) {
      _position = _position;
      
      return normal;
    }
};
