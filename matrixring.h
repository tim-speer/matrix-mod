#ifndef MATRIX_RING_H
#define MATRIX_RING_H

#include "matrixmod.h"
#include "matrixprop.h"

typedef struct {
                 unsigned int n;
                 unsigned int num_mat;
                 MatrixList matrix_list;
                 MatrixProp *props;
               } MatrixRing;

MatrixRing create_matrix_ring(unsigned int dim,
                              unsigned int modulus,
                              unsigned int n);
void free_matrix_ring(MatrixRing *matrix_ring);

#endif
