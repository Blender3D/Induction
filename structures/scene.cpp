#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

class Scene {
  public:
    vector<BaseObject*> objects;
    Camera camera;
    
    BaseObject* getObject(int index) {
      return objects[index];
    }
    
    BaseObject* getObject(const char* name) {
      for (unsigned int i = 0; i < objects.size(); i++) {
        if (objects[i]->name == name) {
          return objects[i];
        }
      }
    }
    
    void addObject(BaseObject* object) {
      objects.push_back(object);
    }
    
    void setCamera(Camera _camera) {
      camera = _camera;
    }
};
