#include <cmath>
#include <stdlib.h>

using namespace std;

class Object {
  public:
    Vector pos;
    Vector diffuse;
    
    ReflectionType reflectionType;
    
    float emittance;
    float IOR;
    float reflection;
    
    virtual float intersection(Ray ray) = 0;
    virtual Vector getNormal(Vector position) = 0;
    virtual Vector getDirection(Vector position, Vector direction) {
      Vector tempNormal = this->getNormal(position);
      
      switch (reflectionType) {
        default:
        case DIFFUSE:
          return RandomNormalInHemisphere(tempNormal);
          break;
        
        case SPECULAR:
          return tempNormal * 2.0 * abs(direction.dot(tempNormal)) + direction;
          break;
        
        case GLASS:
          float internalIndex, externalIndex;
          float theta1 = abs(direction.dot(tempNormal));
          
          if (theta1 >= 0.0) {
            internalIndex = IOR;
            externalIndex = 1.0;
          } else {
            internalIndex = 1.0;
            externalIndex = IOR;
          }
          
          float eta = externalIndex / internalIndex;
          float theta2 = sqrt(1.0 - (eta*eta) * (1.0 - (theta1*theta1)));
          float rs = (externalIndex * theta1 - internalIndex * theta2) / (externalIndex*theta1 + internalIndex * theta2);
          float rp = (internalIndex * theta1 - externalIndex * theta2) / (internalIndex*theta1 + externalIndex * theta2);
          float reflectance = (rs*rs + rp*rp);
          
          if (random_uniform() < reflectance + reflection) {
            return direction + tempNormal * 2.0 * theta1;
          }
          
          return (tempNormal * theta1 + direction) * eta + (tempNormal * -theta2);
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
