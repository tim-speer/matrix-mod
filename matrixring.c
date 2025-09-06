#include "checks.h"
#include "matrixring.h"

MatrixRing create_matrix_ring(unsigned int dim,
                              unsigned int modulus,
                              unsigned int n) {
  check_matrix_params(dim, dim, modulus);
  check_positive(n);

  unsigned int num_mat = num_matrices(dim, dim, modulus);
  MatrixList matrix_list = create_matrix_list(dim, dim, modulus);
  MatrixProp *props = create_matrix_prop_list(dim, dim, modulus); 
  MatrixRing matrix_ring = { n, num_mat, matrix_list, props };
  
  return matrix_ring;
}

void free_matrix_ring(MatrixRing *matrix_ring) {
  free_matrix_list(&matrix_ring->matrix_list);
  free_matrix_prop_list(matrix_ring->props);
}
