#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct Ray {
  Point origin;
  Vector direction;
  
  Ray(Point _origin, Vector _direction) {
    origin = _origin;
    direction = _direction.norm();
  }
  
  Point position(float &time) {
    return origin + direction * time;
  }
  
  bool operator==(Ray &other) {
    return ((other.origin == origin) && (other.direction == direction));
  }
};
