#include <math.h>
#include <stdlib.h>

class Sampler {
  public:
    vector<Point> coordinates;
    int width, height;
    
    virtual void init() = 0;
    Point getPixel(int x, int y) {
      return coordinates[x + y * height];
    }
};