#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "color.h"

class CellImage {
  public:
    int width, height;
    std::vector<ColorXYZ> image;
    
    ~CellImage() {};
    CellImage();
    
    CellImage* operator+ (CellImage);

    void setSize(int, int);
    void setPixel(int, int, ColorXYZ);
    ColorXYZ getPixel(int, int);
    
    void write(const char*, int);
};

#endif
