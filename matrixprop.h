#ifndef MATRIX_PROP_H
#define MATRIX_PROP_H

#include "matrixmod.h"

typedef struct {
                 int idempotent;
                 int unit; 
               } MatrixProp;

MatrixProp create_matrix_prop(void);
int matrices_equal(MatrixMod left, MatrixMod right);
int is_idempotent(MatrixMod matrix);
int is_unit(MatrixMod matrix, MatrixList matrix_list);
void print_matrix_prop(MatrixProp prop);

#endif

