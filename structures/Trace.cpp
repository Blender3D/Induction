#include <math.h>

bool IsVisible(Point point1, Point point2, Scene scene) {
  Ray ray = Ray(point1, point2 - point1);
  
  for (unsigned int i = 0; i < scene.objects.size(); i++) {
    if (scene.objects[i]->getIntersection(ray) > 0.0) {
      return false;
    }
  }

  return true;
}

float GetIntersection(Ray &ray, Scene scene, Object* &hit) {
  int index = -1;
  float result = INFINITY;
  
  for (unsigned int i = 0; i < scene.objects.size(); i++) {
    float test = scene.objects[i]->getIntersection(ray);
    
    if ((0 < test) && (test < result)) {
      result = test;
      index = i;
    }
  }

  if (index == -1) {
    hit = NULL;

    return false;
  } else {
    hit = scene.objects[index];

    return result;
  }
}

LightPath TracePath(Ray ray, Scene scene) {
  Object* hit;
  LightPath path = LightPath();

  float result;
  HitPoint hitPoint;
  Point point;
  Vector normal, direction;

  for (int bounces = 0; bounces < MAX_DEPTH; bounces++) {
    result = GetIntersection(ray, scene, hit);
    
    if (!result) {
      return path;
      break;
    }
    
    point = ray.position(result);
    normal = hit->getNormal(point);
    direction = uniform_hemisphere(normal);

    hitPoint = HitPoint(normal, ray.direction, direction, hit->material);
    path.addPoint(hitPoint);

    ray = Ray(point, direction);
  }
  
  return path;
}

LightPath TraceLightPath(Object* light, Scene scene) {
  Point point = light->getLightSample();
  Vector direction = uniform_hemisphere(light->getNormal(point));
  Ray ray = Ray(point, direction);

  return TracePath(ray, scene);
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

ColorRGB CombinePaths(LightPath path1, LightPath path2, Scene scene) {
  vector<LightPath> paths;
  
  for (unsigned int i = 0; i < path1.points.size(); i++) {
    for (unsigned int j = 0; j < path2.points.size(); j++) {
      
    }
  }

  return ColorRGB();
}

float ShadowRay(Primitive* object1, Primitive* object2) {
  return object2->getIntersection(Ray(object1->position, object1->position - object2->position));
}
