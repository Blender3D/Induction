#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <math.h>

#include "spectrum.h"

class ColorXYZ;

class ColorRGB {
  public:
    float r, g, b;
    
    ~ColorRGB() {};
    
    ColorRGB();
    ColorRGB(float, float, float);
    
    ColorRGB operator+(ColorRGB);
    ColorRGB operator*(ColorRGB);
    ColorRGB operator*(float);
    ColorRGB operator/(float);
    
    friend ColorRGB operator+=(ColorRGB, ColorRGB);
    friend ColorRGB operator*=(ColorRGB, ColorRGB);
    friend ColorRGB operator*=(ColorRGB, float);
    friend ColorRGB operator*=(float, ColorRGB);
    
    ColorRGB clamp();
    ColorRGB clampRGB();
    ColorXYZ toXYZ();
    
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
    
    friend ColorXYZ operator+=(ColorXYZ, ColorXYZ);
    friend ColorXYZ operator*=(ColorXYZ, ColorXYZ);
    friend ColorXYZ operator*=(ColorXYZ, float);
    friend ColorXYZ operator*=(float, ColorXYZ);
    
    ColorRGB toRGB();
    
    friend std::ostream& operator<<(std::ostream&, ColorXYZ&);
};

#endif
