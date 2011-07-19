#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <time.h>

#define PI         3.141592653589793238462643383279
#define INV_PI     0.318309886183790671537767526745

#define TWO_PI     6.283185307179586476925286766559
#define INV_TWO_PI 0.159154943091895335768883763372

#include <omp.h>
#include <GL/freeglut.h>

#include "structures/vector.cpp"
#include "structures/point.cpp"
#include "structures/color.cpp"
#include "structures/ray.cpp"
#include "structures/camera.cpp"
#include "structures/random.cpp"
#include "structures/image.cpp"
#include "structures/boundingbox.cpp"

#include "samplers/sampler.cpp"
#include "samplers/jittered.cpp"
#include "samplers/poisson.cpp"

#include "scene.cpp"
#include "structures/trace.cpp"
#include "loaders/obj.cpp"

using namespace std;

void Render() {
  int samples = 0;
  char sampleString[512];
  
  JitteredSampler* sampler = new JitteredSampler();
  
  sampler->width = scene.camera.canvasWidth;
  sampler->height = scene.camera.canvasHeight;
  
  sampler->init();
  
  cout << "Rendering " << scene.objects.size() << " objects." << endl;
  cout << "Canvas resolution is " << scene.camera.canvasWidth << "x" << scene.camera.canvasHeight << "." << endl;
  cout << endl;
  
  #pragma omp parallel
  {
    while (true) {
      cout << "Tracing sample " << samples;
      cout.flush();
      cout << "\r";
      
      for (float y = 0; y < scene.camera.canvasHeight; y++) {
        for (float x = 0; x < scene.camera.canvasWidth; x++) {
          Point sample = sampler->getPixel(x, y);
          Ray ray = scene.camera.castRay(sample.x, sample.y);
          scene.image->setPixel(x, y, scene.image->getPixel(x, y) + Trace(ray, scene));
        }
      }
      
      if (++samples % 10 == 0) {
        scene.image->write("image.ppm", samples);
      }
      
      #pragma omp barrier
      #pragma omp master
      {
        sprintf(sampleString, "Samples: [%d]", samples);
        glutSetWindowTitle(sampleString);
        
        for (float y = 0; y < scene.camera.canvasHeight; y++) {
          for (float x = 0; x < scene.camera.canvasWidth; x++) {
            glBegin(GL_POINTS);
              Color pixel = (scene.image->getPixel(x, y) / samples).clamp();
              glColor3f(pixel.r, pixel.g, pixel.b);
              glVertex2i(x, y);
            glEnd();
          }
        }
        
        glutSwapBuffers();
      }
    }
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  InitScene();
  
  cout << "/==========================\\" << endl;
  cout << "||  Induction Pathtracer  ||" << endl;
  cout << "||       v0.1 (Git)       ||" << endl;
  cout << "\\==========================/" << endl;
  cout << endl;
  
  ObjLoader* loader = new ObjLoader();
  loader->load("plane.obj");
  scene.loadObjects(loader->objects);
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - scene.camera.canvasWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - scene.camera.canvasHeight) / 2);
  glutInitWindowSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
  glutCreateWindow("Samples: [0]");
  
  glutDisplayFunc(Render);
  
  glViewport(0, 0, scene.camera.canvasWidth, scene.camera.canvasHeight);
  glLoadIdentity();
  glOrtho(0.0, scene.camera.canvasWidth - 1.0, 0.0, scene.camera.canvasHeight - 1.0, -1.0, 1.0);

  glutMainLoop();
}
