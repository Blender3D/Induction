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

#define MAX_DEPTH  6
#define MIN_ROULETTE_DEPTH  3

#ifdef MULTITHREADING
  #include <omp.h>
#endif

#ifdef GUI
  #include <GL/freeglut.h>
#endif

#include "structures/point.h"
#include "structures/vector.h"
#include "structures/color.h"
#include "structures/ray.h"
#include "structures/camera.h"
#include "structures/image.h"
#include "structures/random.cpp"
#include "structures/boundingbox.h"
#include "structures/material.h"
#include "structures/lightpath.h"

#include "samplers/sampler.h"
#include "samplers/jittered.cpp"
#include "samplers/poisson.cpp"

#include "scene.cpp"
#include "structures/trace.cpp"
#include "loaders/obj.cpp"

using namespace std;

void render() {
  int samples = 1;
  int max_threads = 1;

  #pragma omp parallel
  {
    max_threads = omp_get_max_threads();
  }
  
  JitteredSampler* sampler = new JitteredSampler();
  
  sampler->width = scene.camera.canvasWidth;
  sampler->height = scene.camera.canvasHeight;
  
  sampler->init();
  
  cout << "Rendering " << scene.objects.size() << " objects." << endl;
  cout << "Canvas resolution is " << scene.camera.canvasWidth << "x" << scene.camera.canvasHeight << "." << endl;
  cout << endl;

  while (true) {
    for (int y = 0; y < scene.camera.canvasHeight; y++) {
      for (int x = 0; x < scene.camera.canvasWidth; x++) {
        Point sample = sampler->getPixel(x, y);
        Ray ray = scene.camera.castRay(sample.x, sample.y);

        #pragma omp parallel
        {
          LightPath path = TracePath(ray, scene);
          ColorRGB contribution = CalculatePathContribution(path);
          
          scene.image->setPixel(x, y, scene.image->getPixel(x, y) + contribution);
        }
      }

      #pragma omp critical
      {
        printf("Tracing sample %d with %d thread%s [%5.1f%%]", samples, max_threads, (max_threads > 1) ? "s" : "", 100.0 * float(y) / float(scene.camera.canvasHeight));
        cout.flush();
        cout << "\r";

        #ifdef GUI
          glBegin(GL_POINTS);

          for (float i = 0; i < scene.camera.canvasWidth; i++) {
            ColorRGB pixel = (scene.image->getPixel(i, y) / samples);
            glColor3f(pixel.r, pixel.g, pixel.b);
            glVertex2i(i, y);
          }

          glEnd();
         
          if (y % 10 == 0) {
            glutSwapBuffers();
          }
        #endif
      }
    }

    samples += max_threads;
    
    #ifdef GUI
      ostringstream title_stream;
      title_stream << "Samples: [" << samples << "]";

      const string title = title_stream.str();

      glutSetWindowTitle(title.c_str());
    #endif

    scene.image->write("image.ppm", samples);
  }
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  InitScene();
  
  cout << "/==========================\\" << endl;
  cout << "||  Induction Pathtracer  ||" << endl;
  cout << "||       v0.7 (Git)       ||" << endl;
  cout << "\\==========================/" << endl;
  cout << endl;
  
  //ObjLoader* loader = new ObjLoader();
  //loader->load("plane.obj");
  //scene.loadObjects(loader->objects);
  
  #ifdef GUI
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - scene.camera.canvasWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - scene.camera.canvasHeight) / 2);
    glutInitWindowSize(scene.camera.canvasWidth, scene.camera.canvasHeight);
    glutCreateWindow("Samples: [0]");
    
    glutDisplayFunc(render);

    glViewport(0, 0, scene.camera.canvasWidth, scene.camera.canvasHeight);
    glLoadIdentity();
    glOrtho(0.0, scene.camera.canvasWidth - 1.0, 0.0, scene.camera.canvasHeight - 1.0, -1.0, 1.0);

    glutMainLoop();
  #else
    render();
  #endif
}
