#include "matrixmod.h"

MatrixMod create_matrix(const unsigned int size, 
                        const unsigned int modulus, 
                        unsigned int entries[size * size]) {
  
  MatrixMod matrix = { size, modulus, entries }; 
  return matrix;
}
