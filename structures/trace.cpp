#include <cmath>
#include <stdlib.h>

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
  
  _hit = scene.objects[index];
  return (index == -1) ? false : result;
}

Color Trace(Ray ray, Scene scene) {
  Color radiance = Color(1, 1, 1);
  
  for (int bounces = 0; ; bounces++) {
    Object* hit;
    float result = GetIntersection(ray, scene, hit);
    
    if (!result) {
      return Color(0, 0, 0);
      break;
    }
    
    Point point = ray.position(result);
    float emittance = hit->emittance;
    
    radiance *= hit->diffuse * 2;
    
    if (emittance > 0) {
      radiance *= emittance;
      break;
    }
    
    Vector normal = hit->getNormal(point);
    Vector direction = cosine_weighted_hemisphere(normal);
    float radius = sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
    float theta = acos(direction.z / radius);
    float phi = atan(direction.y / direction.x);
    
    radiance *= hit->diffuse;
    radiance *= hit->BRDF(direction, ray.direction);
//    radiance *= abs(normal.dot(direction));
    radiance *= cosine_weighted_hemisphere_pdf(theta, phi);
    
    ray = Ray(point, direction);
  }
  
  return radiance;
}

Color RecursiveTrace(Ray ray, Scene scene, int depth = 0) {
  if (depth > 20) {
    return Color(0, 0, 0);
  }
  
  Object* hit;
  float result = GetIntersection(ray, scene, hit);
  
  if (!result) {
    return Color(0, 0, 0);
  }
  
  Point point = ray.position(result);
  Vector normal = hit->getNormal(point);
  Vector direction = uniform_hemisphere(normal);
  float radius = direction.length();
  float theta = acos(direction.z / radius);
  float phi = atan(direction.y / direction.x);
  
  Ray newRay = Ray(point, direction);
  
  return hit->diffuse
         * RecursiveTrace(newRay, scene, depth + 1)
         * hit->BRDF(ray.direction, newRay.direction)
//         * uniform_hemisphere_pdf(theta, phi)
         + hit->emittance;
}

float ShadowRay(Primitive* object1, Primitive* object2) {
  return object2->getIntersection(Ray(object1->position, object1->position - object2->position));
}
