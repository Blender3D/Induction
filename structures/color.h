#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <math.h>

#include "spectrum.h"

class ColorRGB {
  public:
    float r, g, b;
    
    ~ColorRGB() {};
    
    ColorRGB();
    ColorRGB(float, float, float);
    
    ColorRGB operator+(ColorRGB);
    ColorRGB operator*(float);
    
    friend std::ostream& operator<<(std::ostream&, ColorRGB&);
};

class ColorXYZ {
  public:
    float x, y, z;
    
    ~ColorXYZ() {};
    
    ColorXYZ();
    ColorXYZ(float, float, float);
    
    ColorXYZ operator+(ColorXYZ);
    ColorXYZ operator*(ColorXYZ);
    ColorXYZ operator*(float);
    ColorXYZ operator/(float);
    
    ColorXYZ operator+=(ColorXYZ);
    ColorXYZ operator*=(float);
    
    ColorRGB toRGB();
    
    friend std::ostream& operator<<(std::ostream&, ColorXYZ&);
};

#endif
