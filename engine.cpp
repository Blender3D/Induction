#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "structures.cpp"
#include "objects.cpp"
#include "objects/plane.cpp"
#include "objects/infinite_plane.cpp"
#include "objects/sphere.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
    
  vector<Object*> objects;

  InfinitePlane* bottom = new InfinitePlane();
  bottom->pos = Vector(0, 0, -1);
  bottom->normal = Vector(0, 0, -1);
  bottom->diffuse = Vector(0.75, 0.75, 0.75);
  
  objects.push_back(bottom);
  
  Sphere* light1 = new Sphere();
  light1->pos = Vector(-0.35, 0.35, -0.7);
  light1->radius = 0.3;
  light1->diffuse = Vector(1.0, 0.0, 0.0);
  light1->emittance = 20;
  
  objects.push_back(light1);
  
  Sphere* light2 = new Sphere();
  light2->pos = Vector(0.35, 0.35, -0.7);
  light2->radius = 0.3;
  light2->diffuse = Vector(0.0, 1.0, 0.0);
  light2->emittance = 20;
  
  objects.push_back(light2);
  
  Sphere* light3 = new Sphere();
  light3->pos = Vector(0.0, 0.0, -0.7);
  light3->radius = 0.3;
  light3->diffuse = Vector(0.0, 0.0, 1.0);
  light3->emittance = 20;
  
  objects.push_back(light3);
  
  Camera camera = Camera(Vector(0.0, -15.0, 1.0), Vector(0.0, 1.0, 0.0), ViewPlane(1.0, 0.5, 0.5, 600.0));
  
  int samples = 0;
  Vector *image = new Vector[(int)(camera.viewplane.canvasWidth * camera.viewplane.canvasHeight)];
  
  while (true) {
    samples++;
    cout << "Samples: [" << samples << "]";
    cout.flush();
        
    for (float y = 0.0; y < camera.viewplane.canvasHeight; y++) {
      for (float x = 0.0; x < camera.viewplane.canvasWidth; x++) {
        int sub = (int)(y * camera.viewplane.canvasWidth + x);
        Ray ray = camera.CastRay(camera.viewplane.canvasWidth  - x + random_uniform() - 0.5,
                                 camera.viewplane.canvasHeight - y + random_uniform() - 0.5);
        image[sub] = image[sub] + Trace(ray, objects, 0);
      }
    }
    
    cout << "\r";
    
    if (samples % 100 == 0) {
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
