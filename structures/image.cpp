#include <math.h>
#include <stdio.h>

#include "image.h"

using namespace std;

CellImage::CellImage() {
  
}

CellImage* CellImage::operator+ (CellImage other) {
  CellImage* temp = new CellImage();
  temp->setSize(width, height);
  
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      temp->setPixel(x, y, getPixel(x, y) + other.getPixel(x, y));
    }
  }
  
  return temp;
}

void CellImage::setSize(int _width, int _height) {
  width = _width;
  height = _height;
  
  image.resize(width * height, ColorRGB(0, 0, 0));
}

void CellImage::setPixel(int x, int y, ColorRGB color) {
  image[y * height + x] = color;
}

ColorRGB CellImage::getPixel(int x, int y) {
  return image[y * height + x];
}

void CellImage::write(const char* filename, int samples) {
  ofstream handle;
  handle.open(filename);
  
  handle << "P3" << endl;
  handle << width << " " << height << " " << "255" << endl << endl;
  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      ColorRGB pixel = (getPixel(x, height - y) / samples).clamp();
      
      handle << (int)(pixel.r * 255.0);
      handle << " ";
      handle << (int)(pixel.g * 255.0);
      handle << " ";
      handle << (int)(pixel.b * 255.0); 
      handle << " ";
    }
  }
  
  handle.close();
}
