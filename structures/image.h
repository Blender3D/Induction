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
    std::vector<ColorRGB> image;
    
    ~CellImage() {};
    CellImage();
    
    CellImage* operator+ (CellImage);

    void setSize(int, int);
    void setPixel(int, int, ColorRGB);
    ColorRGB getPixel(int, int);
    
    void write(const char*, int);
};

#endif
