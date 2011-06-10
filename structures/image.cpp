#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

class CellImage {
  public:
    int width, height;
    vector<Color> image;
    
    void setSize(int _width, int _height) {
      width = _width;
      height = _height;
      
      image.resize(width * height, Color(0, 0, 0));
    }
    
    void setPixel(int x, int y, Color color) {
      image[y * height + x] = color;
    }
    
    Color getPixel(int x, int y) {
      return image[y * height + x];
    }
    
    void write(const char* filename, int samples) {
      ofstream handle;
      handle.open(filename);
      
      handle << "P3" << endl;
      handle << width;
      handle << " ";
      handle << height;
      handle << " ";
      handle << "255" << endl << endl;
      
      for (int i = 0; i < width * height; i++) {
        Color pixel = (image[i] / samples).clamp();
        
        handle << (int)(pixel.r * 255.0);
        handle << " ";
        handle << (int)(pixel.g * 255.0);
        handle << " ";
        handle << (int)(pixel.b * 255.0); 
        handle << " ";
      }
      
      handle.close();
    }
};
