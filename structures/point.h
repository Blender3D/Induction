#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

#include "vector.h"

class Point {
  public:
    float x, y, z;
    
    ~Point() {};
    
    Point();
    Point(Vector);
    Point(float);
    Point(float, float);
    Point(float, float, float);
    
    Point operator+(Point);
    Point operator+(Vector);
    Vector operator-(Point);
    
    Point operator*(float);
    Point operator/(float);
    
    bool operator==(Point);
    bool operator!=(Point);
    bool operator>(Point);
    bool operator<(Point);    
    
    float distanceFrom(Point);
    
    friend std::ostream& operator<<(std::ostream&, Point&);
    
    float operator[](int index);
};

#endif
