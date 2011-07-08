#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

inline vector<string> splitstr(const string& s, const string& f) {
  vector<string> temp;
  
  if (f.empty()) {
    temp.push_back(s);
    return temp;
  }

  typedef string::const_iterator iter;
  const iter::difference_type f_size(distance(f.begin(), f.end()));
  
  iter i(s.begin());
  
  for (iter pos; (pos = search(i, s.end(), f.begin(), f.end())) != s.end();) {
      temp.push_back(string(i, pos));
      advance(pos, f_size);
      i = pos;
  }
  
  temp.push_back(string(i, s.end()));
  
  return temp;
}

class ObjLoader {
  public:
    vector<Object*> objects;
    
    void load(const char* filename) {
      Object* object = new Object();
      object->diffuse = Color(1, 1, 1);
      
      vector<Point> vertices;
      vector<Primitive*> faces;
      vector<Vector> normals;
      string materialFile;
      
      ifstream handle;
      string temp;
      
      handle.open(filename);
      
      int line = 1;
      int lines = 0;
      
      while (getline(handle, temp)) {
        lines++;
      }
      
      handle.close();
      handle.open(filename);
      
      while (getline(handle, temp)) {
        string objectName = "";
        
        cout << "Parsing OBJ file [" << (int)((100 * line) / lines) + 1 << "%]";
        cout.flush();
        
        cout << "\r";
        
        if ((temp.find('#') != 0) && (temp.length() > 1)) {
          if ((temp[0] == 'o') && (temp[1] == ' ')) {
            if (objects.size() != 0) {
              objects.push_back(object);
            }
            
            vector<Point> vertices;
            vector<Primitive*> faces;
            vector<Vector> normals;
            
            temp = temp.substr(2, temp.length());
            objectName = temp;
            
            Object* object = new Object();
            object->setName(objectName);
            object->diffuse = Color(1, 1, 1);
          }
          
          if ((temp[0] == 'v') && (temp[1] == ' ')) {
            temp = temp.substr(2, temp.length());
            vector<string> components = splitstr(temp, " ");
            
            vertices.push_back(Point(atof(components[0].c_str()), atof(components[1].c_str()), atof(components[2].c_str())));
          } else if ((temp[0] == 'f') && (temp[1] == ' ')) {
            temp = temp.substr(2, temp.size() - 1);
            vector<string> components = splitstr(temp, " ");
          
            vector<string> normalTemp = splitstr(components[0], "//");
            Vector normal = normals[atof(normalTemp[1].c_str()) - 1];
            
            if (components.size() == 3) {
              Triangle* triangle = new Triangle();
              
              triangle->point1 = vertices[atof(components[0].c_str()) - 1];
              triangle->point2 = vertices[atof(components[1].c_str()) - 1];
              triangle->point3 = vertices[atof(components[2].c_str()) - 1];
              triangle->normal = normal;
              
              faces.push_back(triangle);
            } else if (components.size() == 4) {
              Quadrilateral* quadrilateral = new Quadrilateral();
              
              quadrilateral->point1 = vertices[atof(components[0].c_str()) - 1];
              quadrilateral->point2 = vertices[atof(components[1].c_str()) - 1];
              quadrilateral->point3 = vertices[atof(components[2].c_str()) - 1];
              quadrilateral->point4 = vertices[atof(components[3].c_str()) - 1];
              quadrilateral->normal = normal;
              
              faces.push_back(quadrilateral);
            }
          } else if ((temp[0] == 's') && (temp[1] == ' ')) {
            // Do stuff
          } else if ((temp[0] == 'v') && (temp[1] == 'n')) {
            temp = temp.substr(2, temp.size() - 1);
            vector<string> components = splitstr(temp, " ");
            
            normals.push_back(Vector(atof(components[0].c_str()), atof(components[1].c_str()), atof(components[2].c_str())));
          } else if (temp.find("usemtl") == 0) {
            temp = temp.substr(7, temp.size() - 1);
            
            materialFile = temp;
          }
          
          line++;
        }
      }
      
      cout << endl;
    }
};
