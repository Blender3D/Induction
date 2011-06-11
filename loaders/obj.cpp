#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class ObjLoader {
  public:
    void load(const char* filename) {
      vector<BaseObject*> objects;
      ifstream handle;
      string temp;

      handle.open(filename);
      
      while (getline(handle, temp)) {
        if (temp.find('#') != 0) {
          
        }
      }
    }
};