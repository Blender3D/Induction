#include <math.h>

#ifndef SPECTRUM_H
#define SPECTRUM_H

class Spectrum {
  private:
    static const int min = 390;
    static const int max = 750;
    static const int delta = 10;
    static const int size = (max - min) / delta;
  
  public:
    float spectrum[size];
    
    ~Spectrum() {};
    
    Spectrum();
    Spectrum(float);
    
    //Spectrum fromSamples(int, int[]);

    float operator[](int);
    Spectrum operator+(Spectrum);
    Spectrum operator*(Spectrum);
    
    Spectrum clamp(float, float);
};

#endif
