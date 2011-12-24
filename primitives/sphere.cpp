#include <math.h>
#include <stdlib.h>

class Sphere: public Primitive {
  public:
    float radius;
    
    float getIntersection(Ray ray) {
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
    
    BoundingBox* createBoundingBox() {
      BoundingBox* box = new BoundingBox();
      
      box->corner1 = position - Point(radius);
      box->corner2 = position + Point(radius);
      
      boundingBox = box;
      return box;
    }

    Vector getNormal(Point _position) {
      return (position - _position).norm();
    }
    
    Point getLightSample() {
      return Point(random_vector() * radius);
    }
    
    float getSurfaceArea() {
      return 2 * TWO_PI * radius * radius;
    }
    
    float getVolume() {
      return (4 / 3) * PI * radius * radius * radius;
    }
};
