#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

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
  top->point1 = Vector(-1, 1, 1);
  top->point2 = Vector(1, 1, 1);
  top->point3 = Vector(1, -1, 1);
  top->point4 = Vector(-1, -1, 1);
  top->normal = Vector(0, 0, 1);
  top->diffuse = Vector(0.75, 0.75, 0.75);
  objects.push_back(top);
  
  Quadrilateral* back = new Quadrilateral();
  back->point1 = Vector(-1, 1, -1);
  back->point2 = Vector(1, 1, -1);
  back->point3 = Vector(1, 1, 1);
  back->point4 = Vector(-1, 1, 1);
  back->normal = Vector(0, 1, 0);
  back->diffuse = Vector(0.75, 0.75, 0.75);
  objects.push_back(back);
  
  Quadrilateral* bottom = new Quadrilateral();
  bottom->point1 = Vector(-1, -1, -1);
  bottom->point2 = Vector(1, -1, -1);
  bottom->point3 = Vector(1, 1, -1);
  bottom->point4 = Vector(-1, 1, -1);
  bottom->normal = Vector(0, 0, -1);
  bottom->diffuse = Vector(0.75, 0.75, 0.75);
  objects.push_back(bottom);
  
  Quadrilateral* left = new Quadrilateral();
  left->point1 = Vector(-1, -1, 1);
  left->point2 = Vector(-1, 1, 1);
  left->point3 = Vector(-1, 1, -1);
  left->point4 = Vector(-1, -1, -1);
  left->normal = Vector(-1, 0, 0);
  left->diffuse = Vector(0.75, 0.25, 0.25);
  objects.push_back(left);
  
  Quadrilateral* right = new Quadrilateral();
  right->point1 = Vector(1, -1, 1);
  right->point2 = Vector(1, 1, 1);
  right->point3 = Vector(1, 1, -1);
  right->point4 = Vector(1, -1, -1);
  right->normal = Vector(1, 0, 0);
  right->diffuse = Vector(0.25, 0.25, 0.75);
  objects.push_back(right);
  
  Quadrilateral* light = new Quadrilateral();
  light->point1 = Vector(-0.2, -0.2, 0.999);
  light->point2 = Vector(0.2, -0.2, 0.999);
  light->point3 = Vector(0.2, 0.2, 0.999);
  light->point4 = Vector(-0.2, 0.2, 0.999);
  light->normal = Vector(0, 0, 1);
  light->diffuse = Vector(1, 0.85, 0.43);
  light->emittance = 30;
  objects.push_back(light);
  
  
  Sphere* sphere = new Sphere();
  sphere->pos = Vector(0, 0, -0.5);
  sphere->radius = 0.5;
  sphere->diffuse = Vector(1, 1, 1);
  sphere->reflectionType = SPECULAR;
  objects.push_back(sphere);
  
  /*
  Quadrilateral* object = new Quadrilateral();
  object->point1 = Vector(-0.8, -0.3, 0.3);
  object->point2 = Vector(0.3, -0.3, -0.3);
  object->point3 = Vector(0.3, 0.3, -0.6);
  object->point4 = Vector(-0.3, 0.3, 0.5);
  object->normal = Vector(0, 0, 1);
  object->reflectionType = SPECULAR;
  object->diffuse = Vector(1, 1, 1);
  objects.push_back(object);
  */
  
  Camera camera = Camera(Vector(0, -6.0, 0), Vector(0, 1, 0), ViewPlane(1, 0.5, 0.5, 1200));
  
  int samples = 0;
  Vector *image = new Vector[(int)(camera.viewplane.canvasWidth * camera.viewplane.canvasHeight)];
  
  while (true) {
    samples++;
    cout << "Samples: [" << samples << "]";
    cout.flush();
        
    for (float y = 0; y < camera.viewplane.canvasHeight; y++) {
      for (float x = 0; x < camera.viewplane.canvasWidth; x++) {
        int sub = (int)(y * camera.viewplane.canvasWidth + x);
        Ray ray = camera.CastRay(camera.viewplane.canvasWidth  - x + random_uniform() - 0.5,
                                 camera.viewplane.canvasHeight - y + random_uniform() - 0.5);
        image[sub] = image[sub] + Trace(ray, objects, 0);
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
        Vector pixel = Clamp(image[i] / float(samples));
        
        handle << (int)(pixel.x * 255.0);
        handle << " ";
        handle << (int)(pixel.y * 255.0);
        handle << " ";
        handle << (int)(pixel.z * 255.0); 
        handle << " ";
      }
      
      handle.close();
    }
  }
}
