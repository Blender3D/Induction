#include <cmath>
#include <stdlib.h>

using namespace std;

enum ReflectionType {
  DIFFUSE, SPECULAR, GLASS
};

class Object {
  public:
    Point pos;
    Color diffuse;
    
    ReflectionType reflectionType;
    
    float emittance;
    float IOR;
    float reflection;
    
    virtual float intersection(Ray ray) = 0;
    virtual Vector getNormal(Point position) = 0;
    virtual Vector getDirection(Point position, Vector direction) {
      Vector tempNormal = this->getNormal(position);
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

Color Trace(Ray &ray, vector<Object*> objects) {
  Color radiosity = Color(0, 0, 0);
  Color diffuseProduct = Color(1, 1, 1);
  int bounces = 1;

  while (bounces < 10) {
    int index = -1;
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
      break;
    }
    
    Object *hit = objects[index];
    
    Point point = ray.position(result);
    Vector direction = hit->getDirection(point, ray.direction);

    ray = Ray(point, direction);
    
    diffuseProduct = hit->diffuse * diffuseProduct;
    radiosity = radiosity + diffuseProduct * hit->emittance;
    bounces++;
  }

  return radiosity;
}
