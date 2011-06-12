#include <cmath>
#include <stdlib.h>

using namespace std;
/*
class Object: BaseObject {
  public:
    vector<BaseObject*> objects;
    
    virtual float intersection(Ray ray) {
      int index = -1;
      float result = 1000000.0;
      
      for (unsigned int i = 0; i < objects.size(); i++) {
        BaseObject *target = objects[i];
        float test = target->intersection(ray);
        
        if ((test > 0.0) && (test < result)) {
          result = test;
          index = i;
        }
      }
      
      if (index == -1) {
        return false;
      }
      
      return result;
    }
    
    virtual Vector getNormal(Point positionition) {
      int index = -1;
      float result = 1000000.0;
      
      for (unsigned int i = 0; i < objects.size(); i++) {
        BaseObject *target = objects[i];
        float test = target->intersection(ray);
        
        if ((test > 0.0) && (test < result)) {
          result = test;
          index = i;
        }
      }
      
      if (index == -1) {
        return false;
      }
      
      return result;
    }
    
    virtual Vector getdirection(Point positionition, Vector direction) {
      Vector tempNormal = this->getNormal(positionition);
      Vector v2;
      
      switch (reflectionType) {
        default:
        case DIFFUSE:
          do {
            v2 = Vector(2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0, 2.0 * random_uniform() - 1.0).norm();
          } while (v2.abs() > 1.0);
          
          return v2 * (2 * (v2.dot(tempNormal) < 0.0) - 1);
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
*/