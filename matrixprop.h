#ifndef MATRIX_PROP_H
#define MATRIX_PROP_H

#include "matrixmod.h"

int matrices_equal(MatrixMod left, MatrixMod right);
int is_idempotent(MatrixMod matrix);
int is_unit(MatrixMod matrix, MatrixList matrix_list);

#endif

