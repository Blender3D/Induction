#include <math.h>

#include "transformation.h"
#include "matrix.h"

using namespace std;

Transformation::Transformation() {
  origin = Point();
  matrix.cells = {{1, 0, 0, 0},
                  {0, 1, 0, 0},
                  {0, 0, 1, 0},
                  {0, 0, 0, 1}};
}

Point Transformation::operator*(Point point) {
  return Point(matrix.cells[0][0] * point.x + matrix.cells[1][0] * point.y + matrix.cells[2][0] * point.z + matrix.cells[3][0],
                matrix.cells[0][1] * point.x + matrix.cells[1][1] * point.y + matrix.cells[2][1] * point.z + matrix.cells[3][1],
                matrix.cells[0][2] * point.x + matrix.cells[1][2] * point.y + matrix.cells[2][2] * point.z + matrix.cells[3][2]);
}

Transformation Transformation::scale(float k) {
  Matrix4x4 T = Matrix4x4();
  T.cells = {{k, 0, 0, origin.x},
             {0, k, 0, origin.y},
             {0, 0, k, origin.z},
             {0, 0, 0, 1}};
  
  matrix = T * matrix;
  
  return *this;
}

Transformation Transformation::scale(float x, float y, float z) {
  Matrix4x4 T = Matrix4x4();
  T.cells = {{x, 0, 0, origin.x},
             {0, y, 0, origin.y},
             {0, 0, z, origin.z},
             {0, 0, 0, 1}};
  
  matrix = T * matrix;
  
  return *this;
}

Transformation Transformation::rotate(float x, float y, float z) {
  Matrix4x4 T = Matrix4x4();
  T.cells = {{x, 0, 0, origin.x},
             {0, y, 0, origin.y},
             {0, 0, z, origin.z},
             {0, 0, 0, 1}};
  
  matrix = T * matrix;
  
  return *this;
}

ostream& operator<<(ostream& stream, Transformation& T) {
  stream << "Transformation[";
  
  for (int y = 0; y < 4; y++) {
    stream << T.matrix.cells[y][0]
           << " " << T.matrix.cells[y][1]
           << " " << T.matrix.cells[y][2]
           << " " << T.matrix.cells[y][3];
    
    if (y < 3) {
      stream << "]" << endl << "              [";
    } else {
      stream << "]";
    }
  }
  
  return stream;
}
