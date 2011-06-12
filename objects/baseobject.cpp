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
    virtual Vector getNormal(Point positionition) = 0;
    virtual Vector getdirection(Point positionition, Vector direction) {
      Vector tempNormal = this->getNormal(positionition);
      Vector v2;
      
      switch (reflectionType) {
        default:
        case DIFFUSE:
          return random_vector(tempNormal);
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
