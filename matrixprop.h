#ifndef MATRIX_PROP_H
#define MATRIX_PROP_H

#include "matrixmod.h"

typedef struct {
                 int idempotent;
                 int unit; 
                 int n_torsion_clean;
                 int strongly_n_torsion_clean;
               } MatrixProp;

MatrixProp create_matrix_prop(void);
MatrixProp *create_matrix_prop_list(unsigned int rows,
                                    unsigned int columns,
                                    unsigned int modulus);
void free_matrix_prop_list(MatrixProp *props);
int matrices_equal(MatrixMod left, MatrixMod right);
int calc_idempotents(MatrixList matrix_list, MatrixProp *props);
int is_idempotent(MatrixMod matrix);
int calc_units(MatrixList matrix_list, MatrixProp *props);
int is_unit(MatrixMod matrix, MatrixList matrix_list);
void print_matrix_prop(MatrixProp prop);
int calc_n_torsion_clean(MatrixList matrix_list, 
                         MatrixProp *props, 
                         int n);
int calc_strongly_n_torsion_clean(MatrixList matrix_list,
                                  MatrixProp *props,
                                  int n);

#endif

