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
};

class PoissonSampler: public Sampler {
  public:
    void init() {
      coordinates.resize(width * height, Point(0, 0));
      
      for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          coordinates[x + y * height].x = x + random_uniform();
          coordinates[x + y * height].y = y + random_uniform();
        }
      }
      
      float distance;
      
      for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
          do {
            distance = 0;
            
            for (int dy = -1; dy < 2; dy++) {
              for (int dx = -1; dx < 2; dx++) {
                distance += coordinates[(x + dx) + (y + dy) * height].distanceFrom(coordinates[x + y * height]) / 8;
              }
            }
          
            coordinates[x + y * height].x = x + random_uniform();
            coordinates[x + y * height].y = y + random_uniform();
          } while (distance < 0.5);
        }
      }
    }
};