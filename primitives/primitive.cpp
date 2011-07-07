#include <cmath>
#include <stdlib.h>

using namespace std;

enum ReflectionType {
  DIFFUSE, SPECULAR, GLASS
};

class Primitive {
  public:
    Point position;
    ReflectionType reflectionType;
    BoundingBox* boundingBox;
    
    virtual float getIntersection(Ray ray) = 0;
    virtual Vector getNormal(Point position) = 0;
    virtual BoundingBox* createBoundingBox() = 0;
};