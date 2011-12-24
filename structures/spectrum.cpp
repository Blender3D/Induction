#include <math.h>

#include "spectrum.h"

Spectrum::Spectrum() {
  for (int i = 0; i < size; i++) {
    spectrum[i] = 0;
  }
}

Spectrum::Spectrum(float k) {
  for (int i = 0; i < size; i++) {
    spectrum[i] = k;
  }
}

Spectrum Spectrum::operator+(Spectrum other) {
  Spectrum temp = Spectrum();
  
  for (int i = 0; i < size; i++) {
    temp.spectrum[i] = spectrum[i] + other.spectrum[i];
  }

  return temp;
}

Spectrum Spectrum::operator*(Spectrum other) {
  Spectrum temp = Spectrum();
  
  for (int i = 0; i < size; i++) {
    temp.spectrum[i] = spectrum[i] * other.spectrum[i];
  }

  return temp;
}

Spectrum Spectrum::clamp(float min = 0, float max = INFINITY) {
  Spectrum temp = Spectrum();
  
  for (int i = 0; i < size; i++) {
    temp.spectrum[i] = (min <= spectrum[i]) ? (max >= spectrum[i] ? spectrum[i] : max) : min;
  }

  return temp;
}
