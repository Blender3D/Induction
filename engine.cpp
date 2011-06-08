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
#include "objects/sphere.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
    
  vector<Object*> objects;

  Object* light = new Sphere();
  light->pos = Vector(0.0, 0.0, 2.0);
  light->radius = 0.5;
  light->emittance = 10;
  light->diffuse = Vector(1.0, 0.0, 0.0);
  
  objects.push_back(light);
  
  Object* light2 = new Sphere();
  light2->pos = Vector(0.0, 0.0, -2.0);
  light2->radius = 2.0;
  light2->diffuse = Vector(1.0, 1.0, 1.0);
  
  objects.push_back(light2);
  
  Camera camera = Camera(Vector(0.0, -15.0, 0.0), Vector(0.0, 1.0, 0.0), ViewPlane(1.0, 0.5, 0.5, 300.0));
  
  int samples = 200;
  int count = camera.viewplane.canvasWidth * camera.viewplane.canvasHeight;
  Vector *image = new Vector[count];
  
  for (int sample = 0; sample < samples; sample++) {
    cout << "Sampling [" << sample << "/" << samples << "]";
    cout.flush();
        
    for (float y = 0.0; y < camera.viewplane.canvasHeight; y++) {
      for (float x = 0.0; x < camera.viewplane.canvasWidth; x++) {
        int sub = (int)(y * camera.viewplane.canvasWidth + x);
        Ray ray = camera.CastRay(x + random_uniform() - 0.5, y + random_uniform() - 0.5);
        image[sub] = image[sub] + Trace(ray, objects, 0);
      }
    }
    
    cout << "\r";
  }
  
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
