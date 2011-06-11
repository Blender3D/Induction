#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "structures/vector.cpp"
#include "structures/point.cpp"
#include "structures/color.cpp"
#include "structures/ray.cpp"
#include "structures/camera.cpp"
#include "structures/random.cpp"
#include "structures/image.cpp"

#include "objects/baseobject.cpp"
#include "objects/triangle.cpp"
#include "objects/quadrilateral.cpp"
#include "objects/plane.cpp"
#include "objects/sphere.cpp"

#include "structures/scene.cpp"

#include "loaders/obj.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
  
  ObjLoader loader = ObjLoader();
  loader.load("scene.obj");
  
  Scene scene = Scene();
  
  Quadrilateral* top = new Quadrilateral();
  top->point1 = Point(-1, 1, 1);
  top->point2 = Point(1, 1, 1);
  top->point3 = Point(1, -1, 1);
  top->point4 = Point(-1, -1, 1);
  top->normal = Vector(0, 0, 1);
  top->emittance = 2;
  top->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(top);
  
  Quadrilateral* back = new Quadrilateral();
  back->point1 = Point(-1, 1, -1);
  back->point2 = Point(1, 1, -1);
  back->point3 = Point(1, 1, 1);
  back->point4 = Point(-1, 1, 1);
  back->normal = Vector(0, 1, 0);
  back->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(back);
  
  Quadrilateral* bottom = new Quadrilateral();
  bottom->point1 = Point(-1, -1, -1);
  bottom->point2 = Point(1, -1, -1);
  bottom->point3 = Point(1, 1, -1);
  bottom->point4 = Point(-1, 1, -1);
  bottom->normal = Vector(0, 0, -1);
  bottom->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(bottom);
  
  Quadrilateral* left = new Quadrilateral();
  left->point1 = Point(-1, -1, 1);
  left->point2 = Point(-1, 1, 1);
  left->point3 = Point(-1, 1, -1);
  left->point4 = Point(-1, -1, -1);
  left->normal = Vector(-1, 0, 0);
  left->diffuse = Color(0.75, 0.25, 0.25);
  scene.addObject(left);
  
  Quadrilateral* right = new Quadrilateral();
  right->point1 = Point(1, -1, 1);
  right->point2 = Point(1, 1, 1);
  right->point3 = Point(1, 1, -1);
  right->point4 = Point(1, -1, -1);
  right->normal = Vector(1, 0, 0);
  right->diffuse = Color(0.25, 0.25, 0.75);
  scene.addObject(right);
  
  Sphere* sphere = new Sphere();
  sphere->pos = Point(0, -1, -0.5);
  sphere->radius = 0.5;
  sphere->diffuse = Color(1, 1, 1);
  sphere->reflectionType = GLASS;
  sphere->IOR = 1.03;
  scene.addObject(sphere);
  
  Sphere* sphere2 = new Sphere();
  sphere2->pos = Point(-0.7, 0, -0.9);
  sphere2->radius = 0.3;
  sphere2->diffuse = Color(0.5, 0.5, 0.5);
  sphere2->reflectionType = SPECULAR;
  scene.addObject(sphere2);
  
  Sphere* sphere3 = new Sphere();
  sphere3->pos = Point(0.7, 0, -0.8);
  sphere3->radius = 0.2;
  sphere3->diffuse = Color(0.3, 0.3, 0.3);
  sphere3->reflectionType = SPECULAR;
  scene.addObject(sphere3);
  
  Sphere* sphere4 = new Sphere();
  sphere4->pos = Point(0, 0, 0.1);
  sphere4->radius = 0.1;
  sphere4->diffuse = Color(0.5, 0.5, 0.5);
  sphere4->reflectionType = SPECULAR;
  scene.addObject(sphere4);
  
  Sphere* sphere5 = new Sphere();
  sphere5->pos = Point(0.3, -0.7, -0.85);
  sphere5->radius = 0.15;
  sphere5->diffuse = Color(1, 1, 1);
  sphere5->emittance = 2;
  scene.addObject(sphere5);
  
  Camera camera = Camera();
  camera.pos = Point(0, -4.995, 0);
  camera.setFocus(Point(0, 0, -1));
  camera.setSize(0.5, 0.5);
  camera.offset = 1;
  camera.setPixelDensity(600);
  
  scene.setCamera(camera);
  
  CellImage* image = new CellImage();
  image->setSize(camera.canvasWidth, camera.canvasHeight);
  
  int samples = 0;
  
  while (true) {
    samples++;
    cout << "Samples: [" << samples << "]";
    cout.flush();
        
    for (float y = 0; y < scene.camera.canvasHeight; y++) {
      for (float x = 0; x < scene.camera.canvasWidth; x++) {
        Ray ray = scene.camera.CastRay(scene.camera.canvasWidth  - x, scene.camera.canvasHeight - y);
        image->setPixel(x, y, image->getPixel(x, y) + Trace(ray, scene.objects));
      }
    }
    
    cout << "\r";
    
    if (samples % 10 == 0) {
      image->write("image.ppm", samples);
    }
  }
}
