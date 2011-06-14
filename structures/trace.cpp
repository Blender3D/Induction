#include <cmath>
#include <stdlib.h>

void GetIntersection(Ray &ray, Scene scene, float &_result, BaseObject* &_hit) {
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
  
  _result = (index == -1) ? -1 : result;
  _hit = scene.objects[index];
}
/*
Color LoopTrace(Ray &ray, Scene scene) {
  Color radiosity = Color(0, 0, 0);
  Color diffuseProduct = Color(1, 1, 1);
  float result;
  BaseObject* hit;
  int bounces = 1;
  
  while (bounces < 20) {
    GetIntersection(ray, scene, result, hit);
    
    if (result == -1) {
      break;
    }
    
    Point point = ray.position(result);
    Vector direction = hit->BRDF(point, ray.direction);

    ray = Ray(point, direction);
    
    diffuseProduct = hit->diffuse * diffuseProduct;
    radiosity = radiosity + diffuseProduct * hit->emittance;
    bounces++;
  }

  return radiosity;
}
*/

Color SampleEmitters(Vector direction, Point point) {

}


Color Trace(Ray ray, Scene scene, int depth = 0) {
  float result;
  BaseObject* hit;
  
  GetIntersection(ray, scene, result, hit);
  
  if (result == -1) {
    return Color(0, 0, 0);
  }
  
  Point point = ray.position(result);
  Color illumination = SampleEmitters(ray.direction, point);
  
  Vector direction = hit->BRDF(ray.direction, point);
  Ray newRay = Ray(point, direction);
  
  return hit->diffuse * hit->emittance + hit->BRDF(ray.direction, newRay.direction, point) * cos_omega * Trace(newRay, scene, depth + 1);
}

float ShadowRay(BaseObject* object1, BaseObject* object2) {
  return object2->intersection(Ray(object1->position, object1->position - object2->position));
}

/*

Color LightPath(BaseObject light, Scene scene) {
  float result;
  BaseObject* hit;
  
  Ray ray = Ray(light->position, random_vector());
  
  
  GetIntersection(ray, scene, result, hit);
  
  Point point = ray.position(result);
  Vector direction = hit->BRDF(point, ray.direction);
  
  ray = Ray(point, direction);
  
  return hit->diffuse * (LightTrace(ray, scene.objects) + hit->emittance);
}

vector<Point*> BidirectionalTrace(Ray ray, Scene scene) {
  Color radiosity = Color(0, 0, 0);
  Color diffuseProduct = Color(1, 1, 1);
  float result;
  BaseObject* hit;
  
  vector<Point*> cameraPath;
  
  //
  // Get path of rays from the camera.
  //
  
  vector<BaseObject*> lights;
  
  for (int i = 0; i < scene.objects.size(); i++) {
    if (scene.objects[i]->emittance > 0) {
      lights.push_back(scene.objects[i]);
    }
  }
  
  BaseObject* light = lights[(int)((rand() / MAX_RAND) * lights.size())];
  Ray ray = random_vector();
  
  //
  // Get path of rays from a random light.
  //
  
  while (true) {
    GetIntersection(ray, scene, result, hit);
    
    if (result == -1) {
      break;
    }
    
    Point point = ray.position(result);
    Vector direction = hit->BRDF(point, ray.direction);

    ray = Ray(point, direction);
    
    diffuseProduct = hit->diffuse * diffuseProduct;
    radiosity = radiosity + diffuseProduct * hit->emittance;
  }

  return radiosity;
}
*/
