#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include <omp.h>
#include <GL/glut.h>

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

#include "structures/trace.cpp"
#include "loaders/obj.cpp"

using namespace std;

Scene scene = Scene();
Quadrilateral* topPlane = new Quadrilateral();
Quadrilateral* backPlane = new Quadrilateral();
Quadrilateral* bottomPlane = new Quadrilateral();
Quadrilateral* leftPlane = new Quadrilateral();
Quadrilateral* rightPlane = new Quadrilateral();
Quadrilateral* lightPlane = new Quadrilateral();

Sphere* sphere1 = new Sphere();
Sphere* sphere2 = new Sphere();

Camera camera = Camera();
CellImage* image = new CellImage();

void InitScene() {
  topPlane->point1 = Point(-1, 1, 1);
  topPlane->point2 = Point(1, 1, 1);
  topPlane->point3 = Point(1, -1, 1);
  topPlane->point4 = Point(-1, -1, 1);
  topPlane->normal = Vector(0, 0, 1);
  topPlane->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(topPlane);
  
  backPlane->point1 = Point(-1, 1, -1);
  backPlane->point2 = Point(1, 1, -1);
  backPlane->point3 = Point(1, 1, 1);
  backPlane->point4 = Point(-1, 1, 1);
  backPlane->normal = Vector(0, 1, 0);
  backPlane->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(backPlane);
  
  bottomPlane->point1 = Point(-1, -1, -1);
  bottomPlane->point2 = Point(1, -1, -1);
  bottomPlane->point3 = Point(1, 1, -1);
  bottomPlane->point4 = Point(-1, 1, -1);
  bottomPlane->normal = Vector(0, 0, -1);
  bottomPlane->diffuse = Color(0.75, 0.75, 0.75);
  scene.addObject(bottomPlane);
  
  leftPlane->point1 = Point(-1, -1, 1);
  leftPlane->point2 = Point(-1, 1, 1);
  leftPlane->point3 = Point(-1, 1, -1);
  leftPlane->point4 = Point(-1, -1, -1);
  leftPlane->normal = Vector(-1, 0, 0);
  leftPlane->diffuse = Color(0.75, 0.25, 0.25);
  scene.addObject(leftPlane);
  
  rightPlane->point1 = Point(1, -1, 1);
  rightPlane->point2 = Point(1, 1, 1);
  rightPlane->point3 = Point(1, 1, -1);
  rightPlane->point4 = Point(1, -1, -1);
  rightPlane->normal = Vector(1, 0, 0);
  rightPlane->diffuse = Color(0.25, 0.25, 0.75);
  scene.addObject(rightPlane);
  
  lightPlane->point1 = Point(-0.2, -0.2, 0.999999);
  lightPlane->point2 = Point(0.2, -0.2, 0.999999);
  lightPlane->point3 = Point(0.2, 0.2, 0.999999);
  lightPlane->point4 = Point(-0.2, 0.2, 0.999999);
  lightPlane->normal = Vector(0, 0, 1);
  lightPlane->diffuse = Color(1, 0.85, 0.43);
  lightPlane->emittance = 100;
  scene.addObject(lightPlane);
  
  sphere1->position = Point(-0.5, 0, -0.5);
  sphere1->radius = 0.5;
  sphere1->diffuse = Color(1, 1, 1);
  sphere1->reflectionType = GLASS;
  sphere1->IOR = 1.53;
  scene.addObject(sphere1);
  
  sphere2->position = Point(0.5, 0.5, -0.5);
  sphere2->radius = 0.5;
  sphere2->diffuse = Color(1, 1, 1);
  sphere2->reflectionType = SPECULAR;
  scene.addObject(sphere2);
  
  camera.position = Point(0, -4.995, 0);
  camera.setFocus(Point(0, 0, -1));
  camera.setSize(0.5, 0.5);
  camera.offset = 1;
  camera.setPixelDensity(300);
  
  scene.setCamera(camera);
  
  image->setSize(camera.canvasWidth, camera.canvasHeight);
}

void Render() {  
  int samples = 0;
  
  #pragma omp parallel
  {
    while (samples < 50) {
      samples++;
      
      for (float y = 0; y < scene.camera.canvasHeight; y++) {
        for (float x = 0; x < scene.camera.canvasWidth; x++) {
          Ray ray = scene.camera.CastRay(scene.camera.canvasWidth - x + random_uniform() - 0.5, scene.camera.canvasHeight - y + random_uniform() - 0.5);
          image->setPixel(x, y, image->getPixel(x, y) + Trace(ray, scene));
        }
      }
      
      cout << "Samples: [" << samples << "]";
      cout.flush();
      cout << "\r";
      
      for (float y = 0; y < scene.camera.canvasHeight; y++) {
        for (float x = 0; x < scene.camera.canvasWidth; x++) {
          glBegin(GL_POINTS);
            Color pixel = (image->getPixel(x, y) / samples).clamp();
            glColor3f(pixel.r, pixel.g, pixel.b);
            glVertex2i(x, scene.camera.canvasHeight - y);
          glEnd();
        }
      }
      
      glutSwapBuffers();
      
      if (samples % 10 == 0) {
        image->write("image.ppm", samples);
      }
      
      #pragma omp barrier
      #pragma omp master
      {
        // Core thread only.
      }
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  InitScene();
  
  glutInitWindowSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
  glutInitWindowPosition(-1, -1);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInit(&argc, argv);

  glutCreateWindow("Induction");
  
  glutDisplayFunc(Render);
  
  glViewport(0, 0, scene.camera.canvasWidth, scene.camera.canvasHeight);
  glLoadIdentity();
  glOrtho(0.f, scene.camera.canvasWidth - 1.f, 0.f, scene.camera.canvasHeight - 1.f, -1.f, 1.f);
  
  glutMainLoop();
}