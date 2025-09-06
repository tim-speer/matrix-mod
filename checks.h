#ifndef CHECKS_H
#define CHECKS_H

#include "matrixmod.h"

void check_matrix_row(MatrixMod matrix, unsigned int row);
void check_matrix_column(MatrixMod matrix, unsigned int column);
void check_matrix_dim(MatrixMod matrix,
                      unsigned int row,
                      unsigned int column);
void check_positive(unsigned int num);
void check_modulus(unsigned int modulus);
void check_matrix_params(unsigned int rows,
                         unsigned int columns,
                         unsigned int modulus);
void check_multiply_dim(MatrixMod left, MatrixMod right);
void check_matrices_equal(MatrixMod left, MatrixMod right);
void check_is_square(MatrixMod matrix);

#endif
