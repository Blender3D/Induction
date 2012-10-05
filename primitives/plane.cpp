#include <math.h>
#include <stdlib.h>

using namespace std;

class Plane: public Primitive {
  private:
    const float epsilon = 0.0001;

  public:
    Vector normal;

    float getIntersection(Ray ray) {
      float t;
      float k = ray.direction.dot(normal);

      if (k != 0.0) {
        t = (position - ray.origin).dot(normal) / k;
      } else {
        return false;
      }
      
      if (t < epsilon) {
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
       Vector random;
       int radius = 1000;
       
       do {
         random = random_vector().cross(normal);
       } while (random == Vector());
       
       return random * radius * sqrtf(random_uniform()) + position;
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
