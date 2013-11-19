#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"
#include "point.h"

class Transformation {
  public:
    Matrix4x4 matrix;
    Point origin;
    
    ~Transformation() {};
    
    Transformation();
    
    Point operator*(Point);
    
    Transformation scale(float);
    Transformation scale(float, float, float);
    
    Transformation translate(float, float, float);
    Transformation rotate(float, float, float);
    
    friend std::ostream& operator<<(std::ostream&, Transformation&);
};

#endif
