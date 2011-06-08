#include <math.h>
#include <stdlib.h>

using namespace std;

class Object {
  public:
    Vector pos;
    float emittance;
    Vector diffuse;
    
    virtual float intersection(Ray ray) = 0;
    virtual Vector getNormal(Vector position) = 0;
};

Vector Trace(Ray &ray, vector<Object*> objects, int n = 0) {
  int index = -1;

  if (n > 10) {
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
  Vector direction = RandomNormalInHemisphere(hit->getNormal(point));

  Ray ray2 = Ray(point, direction);
  
  return hit->diffuse * Trace(ray2, objects, n + 1) + hit->emittance;
}
