#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "structures.cpp"
#include "objects.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  srand(time(NULL));
    
  vector<Object*> objects;
  
  Sphere sphere = Sphere();
  sphere.pos = Vector(0, 0, 0);
  sphere.radius = 1;
  sphere.diffuse = Vector(1, 1, 1);
  
  objects.push_back(&sphere);
  
  Camera camera = Camera(Vector(0, -5.0, 0), Vector(0, 0, 0), ViewPlane(0.5, 0.5, 1, 200));
  
  int count = camera.viewplane.canvasWidth * camera.viewplane.canvasHeight;
  Vector *image = new Vector[count];
  
  for (int y = 0; y < camera.viewplane.canvasHeight; y++) {
    for (int x = 0; x < camera.viewplane.canvasWidth; x++) {
      int sub = (int)(y * camera.viewplane.canvasWidth + x);
      Ray ray = camera.CastRay(x, y);
      cout << sub << endl;
      image[sub] = image[sub] + Trace(ray, objects, 0);
    }
  }
  
  int samples = 1;
  
  ofstream handle;
  handle.open("image_cpp.ppm");
  
  handle << "P3\n";
  handle << camera.viewplane.canvasWidth;
  handle << " ";
  handle << camera.viewplane.canvasHeight;
  handle << " ";
  handle << "255\n\n";
  
  for (int i = 0; i < camera.viewplane.canvasWidth * camera.viewplane.canvasHeight; i++) {
    Vector pixel = image[i] / samples;
    
    handle << pixel.x;
    handle << " ";
    handle << pixel.y;
    handle << " ";
    handle << pixel.z;
    handle << " ";
  }
  
  handle.close();
}
