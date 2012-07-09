#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>

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
