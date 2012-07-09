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
  ColorRGB L = ColorRGB(0, 0, 0);
  
  for (int bounces = 0; ; bounces++) {
    Object* hit;
    float result = GetIntersection(ray, scene, hit);
    
    if (!result) {
      return ColorRGB(0, 0, 0);
      break;
    }
    
    Point point = ray.position(result);
    float emittance = hit->material.emittance;
    
    if (emittance > 0) {
      L = L + ColorRGB(emittance, emittance, emittance);
      break;
    }
  }
  
  return L;
}

ColorRGB RecursiveTrace(Ray ray, Scene scene, int depth = 0) {
  if (depth > 20) {
    return ColorRGB(0, 0, 0);
  }
  
  Object* hit;
  float result = GetIntersection(ray, scene, hit);
  
  if (!result) {
    return ColorRGB(0, 0, 0);
  }
  
  Point point = ray.position(result);
  Vector normal = hit->getNormal(point);
  Vector direction = uniform_hemisphere(normal);
  //float radius = direction.length();
  //float theta = acos(direction.z / radius);
  //float phi = atan(direction.y / direction.x);
  
  Ray newRay = Ray(point, direction);
  
  return hit->material.diffuse
         * RecursiveTrace(newRay, scene, depth + 1)
         * hit->material.BRDF(ray.direction, newRay.direction)
//         * uniform_hemisphere_pdf(theta, phi)
         + ColorRGB(hit->material.emittance, hit->material.emittance, hit->material.emittance);
}
float ShadowRay(Primitive* object1, Primitive* object2) {
  return object2->getIntersection(Ray(object1->position, object1->position - object2->position));
}
