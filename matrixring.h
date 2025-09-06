#ifndef MATRIX_RING_H
#define MATRIX_RING_H

#include "matrixmod.h"
#include "matrixprop.h"

typedef struct {
                 unsigned int num_mat;
                 int idempotents;
                 int units;
                 int n_torsion_clean;
                 int n_torsion_checked;
                 int strongly_n_torsion_clean;
                 int strongly_n_torsion_checked;
                 MatrixList matrix_list;
                 MatrixProp *props;
               } MatrixRing;

MatrixRing create_matrix_ring(unsigned int dim,
                              unsigned int modulus);
void free_matrix_ring(MatrixRing *matrix_ring);
void print_matrix_ring(MatrixRing matrix_ring);
void calc_matrix_ring_props(MatrixRing *matrix_ring);

#endif
