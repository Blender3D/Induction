#include <math.h>
#include <algorithm>

#include "material.h"

using namespace std;

Material::Material() {
  diffuse = ColorRGB(1, 1, 1);
  reflectionType = DIFFUSE;

  emittance = 0;
  reflectance = 0;

  IOR = 1.0;
}

float Material::PDF() {
  switch (reflectionType) {
    default:
    case DIFFUSE:
      return INV_TWO_PI;
      break;
  }
}

float Material::BRDF(Vector input, Vector output) {
  input = input;
  output = output;
  
  switch (reflectionType) {
    default:
    case DIFFUSE:
      return reflectance;
      break;
  }
}