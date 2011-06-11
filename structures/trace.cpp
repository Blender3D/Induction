#include <cmath>
#include <stdlib.h>

void GetIntersection(Ray &ray, vector<BaseObject*> objects, float &_result, BaseObject* &_hit) {
  int index = -1;
  float result = 1000000.0;
  unsigned int i;  
  
  for (i = 0; i < objects.size(); i++) {
    BaseObject *target = objects[i];
    float test = target->intersection(ray);
    
    if ((test > 0.0) && (test < result)) {
      result = test;
      index = i;
    }
  }
  
  _result = (index == -1) ? -1 : result;
  _hit = objects[index];
}

Color Trace(Ray &ray, vector<BaseObject*> objects) {
  Color radiosity = Color(0, 0, 0);
  Color diffuseProduct = Color(1, 1, 1);
  float result;
  BaseObject* hit;
  
  
  while (true) {
    GetIntersection(ray, objects, result, hit);
    
    if (result == -1) {
      break;
    }
    
    Point point = ray.position(result);
    Vector direction = hit->getDirection(point, ray.direction);

    ray = Ray(point, direction);
    
    diffuseProduct = hit->diffuse * diffuseProduct;
    radiosity = radiosity + diffuseProduct * hit->emittance;
  }

  return radiosity;
}

Color RecursiveTrace(Ray &ray, vector<BaseObject*> objects) {
  float result;
  BaseObject* hit;
  
  GetIntersection(ray, objects, result, hit);
  
  if (result == -1) {
    return Color(0, 0, 0);
  }
  
  Point point = ray.position(result);
  Vector direction = hit->getDirection(point, ray.direction);
  
  ray = Ray(point, direction);
  
  return hit->diffuse * (RecursiveTrace(ray, objects) + hit->emittance);
}

float ShadowRay(BaseObject* object1, BaseObject* object2) {
  return object2->intersection(Ray(object1->pos, object1->pos - object2->pos));
}

Color LightTrace(BaseObject* light, vector<BaseObject*> objects) {
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
  
  BaseObject *hit = objects[index];
  
  Point point = ray.position(result);
  Vector direction = hit->getDirection(point, ray.direction);

  ray = Ray(point, direction);
  
  return hit->diffuse * (RecursiveTrace(objects, ray) + hit->emittance);
}
