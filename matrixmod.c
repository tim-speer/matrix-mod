#include <math.h>
#include "matrixmod.h"

MatrixMod create_matrix(const unsigned int rows,
			const unsigned int columns, 
                        const unsigned int modulus, 
                        unsigned int entries[rows * columns]) {
  MatrixMod matrix = { rows, columns, modulus, entries }; 
  return matrix;
}

unsigned int num_matrices(unsigned int rows, 
			  unsigned int columns, 
			  unsigned int modulus) {
  return (unsigned int)pow(modulus, rows * columns); 
}

unsigned int *get_matrix_row(MatrixMod matrix, unsigned int row) {
  return matrix.entries + (row - 1) * matrix.columns;
}

unsigned int get_matrix_entry(MatrixMod matrix, 
                              unsigned int row, 
                              unsigned int column) {
  return *(get_matrix_row(matrix, row) + column);
}

