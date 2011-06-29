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

#include "scene.cpp"

#include "structures/trace.cpp"

#include "loaders/obj.cpp"

using namespace std;

void Render() {  
  int samples = 0;
  char sampleString[512];
  
  cout << "Rendering " << scene.objects.size() << " objects." << endl;
  cout << "Canvas resolution is " << scene.camera.canvasWidth << "x" << scene.camera.canvasHeight << "." << endl;
  
  #pragma omp parallel
  {
    while (true) {
      samples++;
      
      cout << endl;
      
      for (float y = 0; y < scene.camera.canvasHeight; y++) {
        cout << "Tracing sample " << samples << ": [" << (int)((100 * y) / scene.camera.canvasHeight) + 1 << "%]";
        cout.flush();
        cout << "\r";
        
        for (float x = 0; x < scene.camera.canvasWidth; x++) {
          Ray ray = scene.camera.CastRay(scene.camera.canvasWidth - x + random_uniform() - 0.5, scene.camera.canvasHeight - y + random_uniform() - 0.5);
          scene.image->setPixel(x, y, scene.image->getPixel(x, y) + Trace(ray, scene));
        }
      }

      if (samples % 10 == 0) {
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
              glVertex2i(x, scene.camera.canvasHeight - y);
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
  /*
  ObjLoader* loader = new ObjLoader();
  loader->load("plane.obj");
  vector<BaseObject*> objects = loader->objects;
  
  for (unsigned int i = 0; i < objects.size(); i++) {
    scene.addObject(objects[i]);
  }
  */
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
