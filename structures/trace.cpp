#include <math.h>

float GetIntersection(Ray &ray, Scene scene, Object* &_hit) {
  int index = -1;
  float result = INFINITY;
  unsigned int i;  
  
  for (i = 0; i < scene.objects.size(); i++) {
    Object *target = scene.objects[i];
    float test = target->getIntersection(ray);
    
    if ((test > 0.0) && (test < result)) {
      result = test;
      index = i;
    }
  }

  if (index != -1) {
    _hit = scene.objects[index];
  } else {
    _hit = NULL;
  }
  
  return (index == -1) ? false : result;
}

ColorRGB Trace(Ray ray, Scene scene) {
  ColorRGB luminance = ColorRGB(0, 0, 0);
  ColorRGB cumilative_diffuse = ColorRGB(1, 1, 1);
  
  Object* hit;

  for (int bounces = 0; bounces < MAX_DEPTH; bounces++) {
    float result = GetIntersection(ray, scene, hit);
    
    if (!result) {
      return luminance;
      break;
    }
    
    Point point = ray.position(result);
    Vector normal = hit->getNormal(point);
    Vector direction = uniform_hemisphere(normal);

    ray = Ray(point, direction);

    cumilative_diffuse = cumilative_diffuse * hit->material.diffuse;
    luminance = luminance + cumilative_diffuse * hit->material.emittance;
  }
  
  return luminance;
}

LightPath TracePath(Ray ray, Scene scene) {
  Object* hit;
  LightPath path = LightPath();
  HitPoint hitPoint;

  for (int bounces = 0; bounces < MAX_DEPTH; bounces++) {
    float result = GetIntersection(ray, scene, hit);
    
    if (!result) {
      return path;
      break;
    }
    
    Point point = ray.position(result);
    Vector normal = hit->getNormal(point);
    Vector direction = uniform_hemisphere(normal);

    hitPoint = HitPoint(normal, ray.direction, direction, hit->material);
    path.addPoint(hitPoint);

    ray = Ray(point, direction);
  }
  
  return path;
}

ColorRGB CalculatePathContribution(LightPath path) {
  ColorRGB luminance = ColorRGB(0, 0, 0);
  ColorRGB cumilative_diffuse = ColorRGB(1, 1, 1);
  HitPoint point;

  for (unsigned int i = 0; i < path.points.size(); i++) {
    point = path.points[i];

    cumilative_diffuse = cumilative_diffuse * point.material.diffuse;
    luminance = luminance + cumilative_diffuse * point.material.emittance;
  }
  
  return luminance;
}

float ShadowRay(Primitive* object1, Primitive* object2) {
  return object2->getIntersection(Ray(object1->position, object1->position - object2->position));
}
