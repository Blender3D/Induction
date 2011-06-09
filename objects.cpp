#include <cmath>
#include <stdlib.h>

using namespace std;

class Object {
  public:
    Vector pos;
    float emittance;
    Vector diffuse;
    ReflectionType reflectionType;
    
    virtual float intersection(Ray ray) = 0;
    virtual Vector getNormal(Vector position) = 0;
    virtual Vector getDirection(Vector position, Vector direction) {
      switch (reflectionType) {
        case DIFFUSE:
        case REFRACTIVE:
          return RandomNormalInHemisphere(this->getNormal(position));
          break;
        
        case SPECULAR:
          Vector tempNormal = this->getNormal(position);
          return tempNormal * 2.0 * abs(direction.dot(tempNormal)) + direction;
          break;
      }
    }
};

Vector Trace(Ray &ray, vector<Object*> objects, int n = 0) {
  int index = -1;

  if (n > 25) {
    return Vector(0.0, 0.0, 0.0);
  }
  
  float result = 1000000.0;
  
  for (unsigned int i = 0; i < objects.size(); i++) {
    Object *target = objects[i];
    float test = target->intersection(ray);
    
    if ((test > 0.0) && (test < result)) {
      result = test;
      index = i;
    }
  }
  
  if (index == -1) {
    return Vector(0.0, 0.0, 0.0);
  }
  
  Object *hit = objects[index];
  
  Vector point = ray.position(result);
  Vector direction = hit->getDirection(point, ray.direction);

  Ray ray2 = Ray(point, direction);
  
  return hit->diffuse * Trace(ray2, objects, n + 1) + hit->emittance;
}
