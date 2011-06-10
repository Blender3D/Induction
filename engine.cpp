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
#include "structures/viewplane.cpp"
#include "structures/camera.cpp"

#include "structures.cpp"

#include "objects.cpp"
#include "objects/quadrilateral.cpp"
#include "objects/plane.cpp"
#include "objects/sphere.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
    
  vector<Object*> objects;
  
  Quadrilateral* top = new Quadrilateral();
  top->point1 = Point(-1, 1, 1);
  top->point2 = Point(1, 1, 1);
  top->point3 = Point(1, -1, 1);
  top->point4 = Point(-1, -1, 1);
  top->normal = Vector(0, 0, 1);
  top->emittance = 2;
  top->diffuse = Color(0.75, 0.75, 0.75);
  objects.push_back(top);
  
  /*
  Plane* top = new Plane();
  top->pos = Point(0, 0, 5);
  top->normal = Vector(0, 0, 1);
  top->emittance = 10;
  top->diffuse = Color(0.75, 0.75, 0.75);
  objects.push_back(top);
  */
  Quadrilateral* back = new Quadrilateral();
  back->point1 = Point(-1, 1, -1);
  back->point2 = Point(1, 1, -1);
  back->point3 = Point(1, 1, 1);
  back->point4 = Point(-1, 1, 1);
  back->normal = Vector(0, 1, 0);
  back->diffuse = Color(0.75, 0.75, 0.75);
  objects.push_back(back);
  
  Quadrilateral* bottom = new Quadrilateral();
  bottom->point1 = Point(-1, -1, -1);
  bottom->point2 = Point(1, -1, -1);
  bottom->point3 = Point(1, 1, -1);
  bottom->point4 = Point(-1, 1, -1);
  bottom->normal = Vector(0, 0, -1);
  bottom->diffuse = Color(0.75, 0.75, 0.75);
  objects.push_back(bottom);
  
  Quadrilateral* left = new Quadrilateral();
  left->point1 = Point(-1, -1, 1);
  left->point2 = Point(-1, 1, 1);
  left->point3 = Point(-1, 1, -1);
  left->point4 = Point(-1, -1, -1);
  left->normal = Vector(-1, 0, 0);
  left->diffuse = Color(0.75, 0.25, 0.25);
  objects.push_back(left);
  
  Quadrilateral* right = new Quadrilateral();
  right->point1 = Point(1, -1, 1);
  right->point2 = Point(1, 1, 1);
  right->point3 = Point(1, 1, -1);
  right->point4 = Point(1, -1, -1);
  right->normal = Vector(1, 0, 0);
  right->diffuse = Color(0.25, 0.25, 0.75);
  objects.push_back(right);
  /*
  Quadrilateral* light = new Quadrilateral();
  light->point1 = Point(-0.2, -0.2, 0.999);
  light->point2 = Point(0.2, -0.2, 0.999);
  light->point3 = Point(0.2, 0.2, 0.999);
  light->point4 = Point(-0.2, 0.2, 0.999);
  light->normal = Vector(0, 0, 1);
  light->diffuse = Color(1, 0.85, 0.43);
  light->emittance = 30;
  objects.push_back(light);
  */
  
  Sphere* sphere = new Sphere();
  sphere->pos = Point(0, 0, -0.5);
  sphere->radius = 0.5;
  sphere->diffuse = Color(1, 1, 1);
  sphere->reflectionType = GLASS;
  sphere->IOR = 1.53;
  objects.push_back(sphere);
  
  Sphere* sphere2 = new Sphere();
  sphere2->pos = Point(-0.7, 0, -0.9);
  sphere2->radius = 0.3;
  sphere2->diffuse = Color(0.5, 0.5, 0.5);
  sphere2->reflectionType = SPECULAR;
  objects.push_back(sphere2);
  
  Sphere* sphere3 = new Sphere();
  sphere3->pos = Point(0.7, 0, -0.8);
  sphere3->radius = 0.2;
  sphere3->diffuse = Color(0.3, 0.3, 0.3);
  sphere3->reflectionType = SPECULAR;
  objects.push_back(sphere3);
  
  Sphere* sphere4 = new Sphere();
  sphere4->pos = Point(0, 0, 0.1);
  sphere4->radius = 0.1;
  sphere4->diffuse = Color(0.5, 0.5, 0.5);
  sphere4->reflectionType = SPECULAR;
  objects.push_back(sphere4);
  
  Sphere* sphere5 = new Sphere();
  sphere5->pos = Point(0.3, -0.7, -0.85);
  sphere5->radius = 0.15;
  sphere5->diffuse = Color(1, 1, 1);
  sphere5->emittance = 2;
  objects.push_back(sphere5);
  
  /*
  Quadrilateral* object = new Quadrilateral();
  object->point1 = Point(-0.8, -0.3, 0.3);
  object->point2 = Point(0.3, -0.3, -0.3);
  object->point3 = Point(0.3, 0.3, -0.6);
  object->point4 = Point(-0.3, 0.3, 0.5);
  object->normal = Vector(0, 0, 1);
  object->reflectionType = SPECULAR;
  object->diffuse = Color(1, 1, 1);
  objects.push_back(object);
  */
  
  Camera camera = Camera(Point(0, -5.0, 0), Point(0, 0, -1), ViewPlane(1, 0.5, 0.5, 600));
  
  int samples = 0;
  Color *image = new Color[(int)(camera.viewplane.canvasWidth * camera.viewplane.canvasHeight)];
  
  while (true) {
    samples++;
    cout << "Samples: [" << samples << "]";
    cout.flush();
        
    for (float y = 0; y < camera.viewplane.canvasHeight; y++) {
      for (float x = 0; x < camera.viewplane.canvasWidth; x++) {
        int sub = (int)(y * camera.viewplane.canvasWidth + x);
        Ray ray = camera.CastRay(camera.viewplane.canvasWidth  - x, camera.viewplane.canvasHeight - y);
        image[sub] = image[sub] + Trace(ray, objects);
      }
    }
    
    cout << "\r";
    
    if (samples % 10 == 0) {
      ofstream handle;
      handle.open("image.ppm");
      
      handle << "P3" << endl;
      handle << camera.viewplane.canvasWidth;
      handle << " ";
      handle << camera.viewplane.canvasHeight;
      handle << " ";
      handle << "255" << endl << endl;
      
      for (int i = 0; i < camera.viewplane.canvasWidth * camera.viewplane.canvasHeight; i++) {
        Color pixel = (image[i] / float(samples)).clamp();
        
        handle << (int)(pixel.r * 255.0);
        handle << " ";
        handle << (int)(pixel.g * 255.0);
        handle << " ";
        handle << (int)(pixel.b * 255.0); 
        handle << " ";
      }
      
      handle.close();
    }
  }
}
