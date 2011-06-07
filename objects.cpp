#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

class Object {
  public:
    Vector pos;
    float emittance;
    Vector diffuse;
    
    float intersection(Ray) {};
    Vector getNormal(Vector) {};
};

class Plane: public Object {
  Vector point1, point2;
  Vector normal;
  
  float intersection(Ray &ray) const {
    float k, t, test1, test2;
    Vector point;
    Vector toPoint;
    
    k = ray.direction.dot(normal);

    if (k != 0) {
      t = (pos - ray.origin).dot(normal) / k;
    } else {
      return false;
    }
    
    if (t < 0.0000001) {
      return false;
    }
    
    point = ray.position(t);
    toPoint = point - pos;
    
    test1 = toPoint.dot(point1);
    
    if (test1 < 0 || test1 > (point1 - pos).abs()) {
      return false;
    }
    
    test2 = toPoint.dot(point2);
    
    if (test2 < 0 || test2 > (point2 - pos).abs()) {
      return false;
    }
    
    return t;
  }
  
  Vector getNormal(Vector position) const {
    return normal;
  }
};

class Sphere: public Object {
  public:
    float radius;
    
    float intersection(Ray &ray) const {
      Vector distance;
      float b, c, d;
      
      distance = ray.origin - pos;
      b = distance.dot(ray.direction);
      c = distance.dot(distance) - radius*radius;
      d = b*b - c;
      
      if (d > 0) {
        return -b - sqrt(d);
      } else {
        return false;
      }
    }
    
    Vector getNormal(Vector position) const {
      return (position - pos).norm();
    }
};

Vector Trace(Ray &ray, vector<Object*> objects, float roulette, int n = 0) {
  float test;
  int index = -1;
  cout << "Tracing";
  if ((n > 10) || (random_uniform() < roulette)) {
    return Vector(0, 0, 0);
  }
  
  float result = 1000000;
  
  for (int i = 0; i < objects.size(); i++) {
    Object target = *objects[i];
    float test = target.intersection(ray);
    
    if ((test > 0) && (test < result)) {
      result = test;
      index = i;
    }
  }
  
  if (index == -1) {
    return Vector(0, 0, 0);
  }
  
  Object hit = *objects[index];
  
  Vector point = ray.position(result);
  Vector normal = hit.getNormal(point);
  
  Vector direction = RandomNormalInHemisphere(normal);
  Ray ray2 = Ray(point, direction);
  
  return hit.diffuse * (Trace(ray2, objects, roulette, n + 1) + hit.emittance);
}
