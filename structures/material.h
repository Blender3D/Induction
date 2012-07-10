#ifndef MATERIAL_H
#define MATERIAL_H

#define PI         3.141592653589793238462643383279
#define INV_PI     0.318309886183790671537767526745

#define TWO_PI     6.283185307179586476925286766559
#define INV_TWO_PI 0.159154943091895335768883763372

#include "vector.h"
#include "color.h"

using namespace std;

enum ReflectionType {
  DIFFUSE, SPECULAR, GLASS
};

class Material {
  public:
    float emittance;
    float reflectance;
    float IOR;
    
    float PDF();
    float BRDF(Vector, Vector);

    ColorRGB diffuse;

    ReflectionType reflectionType;

  	~Material() {};
  	Material();
};

#endif
