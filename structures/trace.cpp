#include <cmath>
#include <stdlib.h>

float GetIntersection(Ray &ray, Scene scene, BaseObject* &_hit) {
  int index = -1;
  float result = 1000000.0;
  unsigned int i;  
  
  for (i = 0; i < scene.objects.size(); i++) {
    BaseObject *target = scene.objects[i];
    float test = target->intersection(ray);
    
    if ((test > 0.0) && (test < result)) {
      result = test;
      index = i;
    }
  }
  
  _hit = scene.objects[index];
  return (index == -1) ? -1 : result;
}

Color Trace(Ray ray, Scene scene) {
  Color radiance = Color(1, 1, 1);
  int bounces = 0;
  float termination_probability = 0.5;
  float termination_constant = 0;
  
  while (++bounces < 20) {
    /*
    if (random_uniform() < termination_probability) {
      radiance *= termination_constant;
    }

    radiance *= 1 / (1 - termination_probability);
    */
    BaseObject* hit;
    float result = GetIntersection(ray, scene, hit);
    
    if (result == -1) {
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
    Vector direction = uniform_hemisphere(normal);
    //float radius = sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
    //float theta = acos(direction.z / radius);
    //float phi = atan(direction.y / direction.x);
    
    radiance *= hit->diffuse * hit->BRDF(direction, ray.direction) * abs(normal.dot(direction));
    radiance *= uniform_hemisphere_pdf(0, 0);//theta, phi);
    
    //termination_probability = 1 - abs(normal.dot(direction));
    
    ray = Ray(point, direction);
  }
  
  return radiance;
}

float ShadowRay(BaseObject* object1, BaseObject* object2) {
  return object2->intersection(Ray(object1->position, object1->position - object2->position));
}
