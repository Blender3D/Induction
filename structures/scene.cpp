#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Scene {
  public:
    vector<BaseObject*> objects;
    vector<BaseObject*> lights;
    Camera camera;
    CellImage* image;
    
    BaseObject* getObject(const char* name) {
      for (unsigned int i = 0; i < objects.size(); i++) {
        if (objects[i]->name == name) {
          return objects[i];
        }
      }
    }
    
    void addObject(BaseObject* object) {
      objects.push_back(object);
      
      if (object->emittance > 0) {
        lights.push_back(object);
      }
    }
    
    void setCamera(Camera _camera) {
      camera = _camera;
    }
    
    void setImage(CellImage* _image) {
      image = _image;
    }
};
