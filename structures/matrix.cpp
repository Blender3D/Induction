#include <math.h>

#include "matrix.h"

using namespace std;

Matrix4x4::Matrix4x4() {
  for (int i = 0; i < 4; i++) {
    vector<float> row;
    
    for (int j = 0; j < 4; j++) {
      row.push_back(i * j);
    }
    
    cells.push_back(row);
  }
}

Matrix4x4::Matrix4x4(float _cells[4][4]) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      cells[y][x] = _cells[y][x];
    }
  }
}

Matrix4x4 Matrix4x4::operator+(Matrix4x4 other) {
  Matrix4x4 temp = Matrix4x4();;
  
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      temp.cells[y][x] = cells[y][x] + other.cells[y][x];
    }
  }
  
  return temp;
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4 other) {
  Matrix4x4 temp = Matrix4x4();
  
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      temp.cells[y][x] = cells[y][x] - other.cells[y][x];
    }
  }
  
  return temp;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 other) {
  Matrix4x4 temp = Matrix4x4();
  
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      float temp_cell = 0;
      
      for (int z = 0; z < 4; z++) {
        temp_cell += cells[y][z] * other.cells[z][x];
      }

      temp.cells[y][x] = temp_cell;
    }
  }
  
  return temp;
}

ostream& operator<<(ostream& stream, Matrix4x4& matrix) {
  stream << "Matrix4x4[";
  
  for (int y = 0; y < 4; y++) {
    stream << matrix.cells[y][0]
           << " " << matrix.cells[y][1]
           << " " << matrix.cells[y][2]
           << " " << matrix.cells[y][3];
    
    if (y < 3) {
      stream << "]" << endl << "         [";
    } else {
      stream << "]";
    }
  }
  
  return stream;
}
