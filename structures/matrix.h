#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Matrix4x4 {
  public:
    vector< vector<float> > cells;
    
    ~Matrix4x4() {};
    
    Matrix4x4();
    Matrix4x4(float[4][4]);
    
    Matrix4x4 operator+(Matrix4x4);
    Matrix4x4 operator-(Matrix4x4);
    Matrix4x4 operator*(Matrix4x4);
    
    friend std::ostream& operator<<(std::ostream&, Matrix4x4&);
};

#endif
