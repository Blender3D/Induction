#include <math.h>
#include <stdlib.h>

class JitteredSampler: public Sampler {
  public:
    void init() {
      coordinates.resize(width * height, Point(0, 0));
      
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          coordinates[x + y * height].x = x + random_uniform();
          coordinates[x + y * height].y = y + random_uniform();
        }
      }
    }

    Point getPixel(int x, int y) {
      return Point(x + random_uniform(), y + random_uniform());
    }
};
