#include <math.h>
#include <algorithm>

#include "color.h"

using namespace std;

ColorRGB::ColorRGB() {
  r = 0;
  g = 0;
  b = 0;
}

ColorRGB::ColorRGB(float _r, float _g, float _b) {
  r = _r;
  g = _g;
  b = _b;
}

ColorRGB ColorRGB::operator+(ColorRGB color) {
  return ColorRGB(r + color.r, g + color.g, b + color.b);
}

ColorRGB ColorRGB::operator*(ColorRGB color) {
  return ColorRGB(r * color.r, g * color.g, b * color.b);
}

ColorRGB ColorRGB::operator*(float k) {
  return ColorRGB(r * k, g * k, b * k);
}

ColorRGB ColorRGB::operator/(float k) {
  return ColorRGB(r / k, g / k, b / k);
}

ColorRGB operator +=(ColorRGB self, ColorRGB other) {
  self = self + other;
  return self;
}

ColorRGB operator *=(ColorRGB self, ColorRGB other) {
  self = self * other;
  return self;
}

ColorRGB operator *=(ColorRGB self, float other) {
  self = ColorRGB(self.r * other, self.g * other, self.b * other);
  return self;
}

ColorRGB operator *=(float other, ColorRGB self) {
  self = ColorRGB(self.r * other, self.g * other, self.b * other);
  return self;
}

ColorRGB ColorRGB::clamp() {
  ColorRGB temp = ColorRGB(r, g, b);
  
  if (temp.r < 0) {
    temp.r = 0;
  } else if (temp.r > 1) {
    temp.r = 1;
  }

  if (temp.g < 0) {
    temp.g = 0;
  } else if (temp.g > 1) {
    temp.g = 1;
  }

  if (temp.b < 0) {
    temp.b = 0;
  } else if (temp.b > 1) {
    temp.b = 1;
  }
  
  return temp;
}

ColorRGB ColorRGB::clampRGB() {
  ColorRGB clamped_temp = this->clamp() * 255;
  
  return ColorRGB((int)(clamped_temp.r), (int)(clamped_temp.g), (int)(clamped_temp.b));
}

ColorXYZ ColorRGB::toXYZ() {
  return ColorXYZ(0.412453 * r  + 0.35758 * g  +  0.180423 * b,
                  0.212671 * r  + 0.71516 * g  + 0.0721688 * b,
                 0.0193338 * r + 0.119194 * g  +  0.950227 * b);
}

ostream& operator<<(ostream& stream, ColorRGB& color) {
  stream << "ColorRGB(" << color.r << ", " << color.g << ", " << color.b << ")";
  
  return stream;
}



ColorXYZ::ColorXYZ() {
  x = 0;
  y = 0;
  z = 0;
}

ColorXYZ::ColorXYZ(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

ColorXYZ ColorXYZ::operator+(ColorXYZ color) {
  return ColorXYZ(x + color.x, y + color.y, z + color.z);
}

ColorXYZ ColorXYZ::operator*(ColorXYZ color) {
  return ColorXYZ(x * color.x, y * color.y, z * color.z);
}

ColorXYZ ColorXYZ::operator*(float k) {
  return ColorXYZ(x * k, y * k, z * k);
}

ColorXYZ ColorXYZ::operator/(float k) {
  return ColorXYZ(x / k, y / k, z / k);
}

ColorXYZ operator +=(ColorXYZ self, ColorXYZ other) {
  self = self + other;
  return self;
}

ColorXYZ operator *=(ColorXYZ self, ColorXYZ other) {
  self = self * other;
  return self;
}

ColorXYZ operator *=(ColorXYZ self, float other) {
  self = ColorXYZ(self.x * other, self.y * other, self.z * other);
  return self;
}

ColorXYZ operator *=(float other, ColorXYZ self) {
  self = ColorXYZ(self.x * other, self.y * other, self.z * other);
  return self;
}

ColorRGB ColorXYZ::toRGB() {
  return ColorRGB(3.240479 * x - 1.537150 * y - 0.498535 * z,
                 -0.969256 * x + 1.875991 * y + 0.041556 * z,
                  0.055648 * x - 0.204043 * y + 1.057311 * z);
}

ostream& operator<<(ostream& stream, ColorXYZ& color) {
  stream << "ColorXYZ(" << color.x << ", " << color.y << ", " << color.z << ")";
  
  return stream;
}
