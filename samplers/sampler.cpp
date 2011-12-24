#include <math.h>
#include <vector>

#include "sampler.h"
#include "../structures/point.h"

using namespace std;

Sampler::Sampler() {
    
}

Point Sampler::getPixel(int x, int y) {
  return coordinates[x + y * height];
}
