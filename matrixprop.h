#ifndef MATRIX_PROP_H
#define MATRIX_PROP_H

#include "matrixmod.h"

typedef struct {
                 int idempotent;
                 int unit; 
               } MatrixProp;

MatrixProp create_matrix_prop(void);
MatrixProp *create_matrix_prop_list(unsigned int rows,
                                    unsigned int columns,
                                    unsigned int modulus);
void free_matrix_prop_list(MatrixProp *props);
int matrices_equal(MatrixMod left, MatrixMod right);
void calc_idempotents(MatrixList matrix_list, MatrixProp *props);
int is_idempotent(MatrixMod matrix);
int is_unit(MatrixMod matrix, MatrixList matrix_list);
void print_matrix_prop(MatrixProp prop);

#endif

