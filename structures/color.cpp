#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct Color {
  float r, g, b;
  
  Color(float _r = 0.0, float _g = 0.0, float _b = 0.0) {
    r = _r;
    g = _g;
    b = _b;
  }
  
  Color operator +(Color other) const {
    return Color(r + other.r, g + other.g, b + other.b);
  }
  
  Color operator +(float other) const {
    return Color(r + other, g + other, b + other);
  }
  
  Color operator -(Color other) const {
    return Color(r - other.r, g - other.g, b - other.b);
  }
  
  Color operator *(float other) const {
    return Color(r * other, g * other, b * other);
  }
  
  Color operator *(Color other) const {
    return Color(r * other.r, g * other.g, b * other.b);
  }
  
  Color operator /(float other) const {
    return *this * (1.0 / other);
  }
  
  bool operator ==(Color other) {
    return ((other.r == r) && (other.g == g) && (other.b == b));
  }
  
  Color operator +=(Color other) {
    *this = *this + other;
    return *this;
  }
  
  Color operator +=(float other) {
    *this = *this + other;
    return *this;
  }
  
  Color operator -=(Color other) {
    *this = *this - other;
    return *this;
  }
  
  Color operator -=(float other) {
    *this = *this - other;
    return *this;
  }
  
  Color operator *=(Color other) {
    *this = *this * other;
    return *this;
  }
  
  Color operator *=(float other) {
    *this = *this * other;
    return *this;
  }
  
  Color operator /=(float other) {
    *this = *this / other;
    return *this;
  }
  
  Color clamp() {
    return Color(r > 1 ? 1 : r, g > 1 ? 1 : g, b > 1 ? 1 : b);
  }
};
