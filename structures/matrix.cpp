#include <math.h>
#include <stdlib.h>

using namespace std;

class Matrix {
  public:
    int width, height;
    vector<float> contents;
    
    float get(int x, int y) {
      return contents[height * y + x];
    }
    
    void set(int x, int y, float value) {
      contents[height * y + x] = value;
    }
    
    Matrix operator +(Matrix other) {
      Matrix *temp = new Matrix();
      temp->setSize(width, height);
      
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          temp->set(x, y, get(x, y) + other.get(x, y));
        }
      }
      
      return *temp;
    }
    
    Matrix operator -(Matrix other) {
      Matrix *temp = new Matrix();
      temp->setSize(width, height);
      
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          temp->set(x, y, get(x, y) - other.get(x, y));
        }
      }
      
      return *temp;
    }
    
    Matrix operator *(Matrix other) {
      Matrix *temp = new Matrix();
      temp->setSize(other.width, height);
      
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          for (int i = 0; i < width; x++) {
            temp->set(x, y, temp->get(x, y) + get(i, y) * other.get(x, i));
          }
        }
      }
      
      return *temp;
    }
    
    void setSize(int _width, int _height) {
      width = _width;
      height = _height;
      
      contents.resize(width * height, 0);
    }
};
