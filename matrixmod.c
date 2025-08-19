#include <math.h>
#include "matrixmod.h"

MatrixMod create_matrix(const unsigned int size, 
                        const unsigned int modulus, 
                        unsigned int entries[size * size]) {
  
  MatrixMod matrix = { size, modulus, entries }; 
  return matrix;
}

unsigned int num_matrices(unsigned int size, unsigned int modulus) {
  return (unsigned int)pow(modulus, size * size); 
}

unsigned int get_matrix_entry(MatrixMod matrix, 
                              unsigned int row, 
                              unsigned int column) {
  return *(matrix.entries + row * matrix.size + column);
}
