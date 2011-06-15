#include <cmath>
#include <stdlib.h>

using namespace std;

enum ReflectionType {
  DIFFUSE, SPECULAR, GLASS
};

class BaseObject {
  public:
    Point position;
    Color diffuse;
    const char* name;
    
    ReflectionType reflectionType;
    
    float emittance;
    float IOR;
    float reflection;
    
    virtual float intersection(Ray ray) = 0;
    virtual Vector getNormal(Point position) = 0;
    float BRDF(Vector input, Vector output) {
      switch (reflectionType) {
        default:
        case DIFFUSE:
          return 1;
          break;
      }
    }
    
    Color BRDF(Vector input, Vector output, Point position) {
      Vector tempNormal = this->getNormal(position);
      Vector v2;
      
      switch (reflectionType) {
        default:
        case DIFFUSE:
          return diffuse * output.dot(tempNormal);
          break;
        /*
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
          */
      }
    }
};
/*
Color Radiance(BaseObject* object, int samples, Point point) {
  Color total = Emitted(point, outDirection);
  Vector normal = object->getNormal(point);
  
  for (int i = 0; i < samples; i++) {
    inDirection = -random_vector(normal);
    outDirection = random_vector(normal);
    
    total += object->BRDF(point, inDirection, outDirection)
           * Radiance(point, inDirection)
           * -inDirection.dot(object->normal(point));
  }
}
*/