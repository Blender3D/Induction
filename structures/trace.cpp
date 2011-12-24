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
  
  _hit = scene.objects[index];
  return (index == -1) ? false : result;
}

ColorXYZ Trace(Ray ray, Scene scene) {
  ColorXYZ L = ColorXYZ(0, 0, 0);
  
  for (int bounces = 0; ; bounces++) {
    Object* hit;
    float result = GetIntersection(ray, scene, hit);
    
    if (!result) {
      return ColorXYZ(0, 0, 0);
      break;
    }
    
    Point point = ray.position(result);
    float emittance = hit->emittance;
    
    if (emittance > 0) {
      L = L + ColorXYZ(emittance, emittance, emittance);
      break;
    }
  }
  
  return L;
}

ColorXYZ RecursiveTrace(Ray ray, Scene scene, int depth = 0) {
  if (depth > 20) {
    return ColorXYZ(0, 0, 0);
  }
  
  Object* hit;
  float result = GetIntersection(ray, scene, hit);
  
  if (!result) {
    return ColorXYZ(0, 0, 0);
  }
  
  Point point = ray.position(result);
  Vector normal = hit->getNormal(point);
  Vector direction = uniform_hemisphere(normal);
  //float radius = direction.length();
  //float theta = acos(direction.z / radius);
  //float phi = atan(direction.y / direction.x);
  
  Ray newRay = Ray(point, direction);
  
  return hit->diffuse
         * RecursiveTrace(newRay, scene, depth + 1)
         * hit->BRDF(ray.direction, newRay.direction)
//         * uniform_hemisphere_pdf(theta, phi)
         + ColorXYZ(hit->emittance, hit->emittance, hit->emittance);
}
float ShadowRay(Primitive* object1, Primitive* object2) {
  return object2->getIntersection(Ray(object1->position, object1->position - object2->position));
}
