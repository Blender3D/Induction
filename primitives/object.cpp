#include <math.h>
#include <stdlib.h>

using namespace std;

class Object {
  public:
    vector<Primitive*> objects;
    Primitive* lastHit;
    BoundingBox* boundingBox;
    string name;
    
    Point position;
    ColorXYZ diffuse;
    
    ReflectionType reflectionType;
    
    float emittance;
    float IOR;
    float reflectance;
    
    void setName(string _name) {
      name = _name;
    }
    
    void addPrimitive(Primitive* primitive) {
      objects.push_back(primitive);
    }
    
    BoundingBox* createBoundingBox() {
      Point minimum = Point(INFINITY);
      Point maximum = Point(-INFINITY);
      
      for (unsigned int i = 0; i < objects.size(); i++) {
        BoundingBox* box = objects[i]->createBoundingBox();
        
        if (box->corner1 < minimum) {
          minimum = box->corner1;
        }
        
        if (box->corner2 > maximum) {
          maximum = box->corner2;
        }
      }
      
      boundingBox->corner1 = minimum;
      boundingBox->corner2 = maximum;
      
      return boundingBox;
    }
    
    float getIntersection(Ray &ray) {
      //if (!boundingBox->getIntersection(ray)) {
      //  return false;
      //}

      int index = -1;
      float result = INFINITY;
      
      for (unsigned int i = 0; i < objects.size(); i++) {
        Primitive* target = objects[i];
        float test = target->getIntersection(ray);
        
        if ((test > 0.0) && (test < result)) {
          result = test;
          index = i;
        }
      }
      
      if (index == -1) {
        return false;
      }
      
      lastHit = objects[index];
      return result;
    }
    
    Vector getNormal(Point position) {
      return lastHit->getNormal(position);
    }
    
    Point getLightSample() {
      return objects[random_int(objects.size())]->getLightSample();
    }
    
    float PDF() {
      switch (reflectionType) {
        default:
        case DIFFUSE:
          return INV_TWO_PI;
          break;
      }
    }
    
    float BRDF(Vector input, Vector output) {
      input = input;
      output = output;
      
      switch (reflectionType) {
        default:
        case DIFFUSE:
          return reflectance;
          break;
      }
    }
};
