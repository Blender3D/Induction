#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Scene {
  public:
    vector<Object*> objects;
    vector<Object*> lights;
    Camera camera;
    CellImage* image;
    
    Object* getObject(const char* name) {
      for (unsigned int i = 0; i < objects.size(); i++) {
        if (objects[i]->name == name) {
          return objects[i];
        }
      }
    }
    
    void addObject(Object* object) {
      //object->createBoundingBox();
      objects.push_back(object);
      
      if (object->emittance > 0) {
        lights.push_back(object);
      }
    }
    
    void addObject(Primitive* _object) {
      Object* object = new Object();
      object->objects.push_back(_object);
      //object->createBoundingBox();
      
      addObject(object);
    }
    
    void setCamera(Camera _camera) {
      camera = _camera;
    }
    
    void setImage(CellImage* _image) {
      image = _image;
    }
    
    void loadObjects(vector<Object*> objects) {
      for (unsigned int i = 0; i < objects.size(); i++) {
        addObject(objects[i]);
      }
    }
};
