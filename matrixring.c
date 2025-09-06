#include <stdio.h>
#include "checks.h"
#include "matrixring.h"

MatrixRing create_matrix_ring(unsigned int dim,
                              unsigned int modulus) {
  check_matrix_params(dim, dim, modulus);

  unsigned int num_mat = num_matrices(dim, dim, modulus);
  MatrixList matrix_list = create_matrix_list(dim, dim, modulus);
  MatrixProp *props = create_matrix_prop_list(dim, dim, modulus); 
  MatrixRing matrix_ring = { num_mat, -1, -1, -1, 1, -1, 1, matrix_list, props };
  
  return matrix_ring;
}

void free_matrix_ring(MatrixRing *matrix_ring) {
  free_matrix_list(&matrix_ring->matrix_list);
  free_matrix_prop_list(matrix_ring->props);
}

void print_matrix_ring(MatrixRing matrix_ring) {
  printf("\nnum_mat = %u\n", matrix_ring.num_mat);
  printf("idempotents = %d\n", matrix_ring.idempotents);
  printf("units = %d\n", matrix_ring.units);
  printf("N-Torsion Clean = %d\n", matrix_ring.n_torsion_clean);
  printf("N-Torsion Checked = %d\n", matrix_ring.n_torsion_checked);
  printf("Strongly N-Torsion Clean = %d\n", matrix_ring.strongly_n_torsion_clean);
  printf("Strongly N-Torsion Checked = %d\n", matrix_ring.strongly_n_torsion_checked);
  printf("rows = %u\n", matrix_ring.matrix_list.rows);
  printf("columns = %u\n", matrix_ring.matrix_list.columns);
  printf("modulus = %u\n\n", matrix_ring.matrix_list.modulus);

  /*for (unsigned int i = 0; i < matrix_ring.num_mat; i++) {
    print_matrix(matrix_ring.matrix_list.matrices[i]);
    print_matrix_prop(matrix_ring.props[i]);
    printf("\n");
  }*/
}

void calc_matrix_ring_props(MatrixRing *matrix_ring) {
  if (matrix_ring->idempotents == -1) {
    calc_idempotents(matrix_ring->matrix_list, matrix_ring->props);
    matrix_ring->idempotents = 1;
  }  

  if (matrix_ring->units == -1) {
    calc_units(matrix_ring->matrix_list, matrix_ring->props);
    matrix_ring->units = 1;
  }

  if (matrix_ring->n_torsion_clean == -1 || matrix_ring->n_torsion_clean == 0) {
    matrix_ring->n_torsion_clean = calc_n_torsion_clean(matrix_ring->matrix_list, 
                                                        matrix_ring->props,
                                                        matrix_ring->n_torsion_checked + 1);
    matrix_ring->n_torsion_checked++; 
  }

  if (matrix_ring->strongly_n_torsion_clean == -1 ||
      matrix_ring->strongly_n_torsion_clean == 0) {
    matrix_ring->strongly_n_torsion_clean = calc_strongly_n_torsion_clean(matrix_ring->matrix_list,
                                                                          matrix_ring->props,
                                                                          matrix_ring->strongly_n_torsion_checked + 1);
    matrix_ring->strongly_n_torsion_checked++;  
  }

}

void iter_calc_matrix_ring_props(MatrixRing *matrix_ring, unsigned int iters) {
  for (unsigned int i = 0; i < iters; i++) {
    calc_matrix_ring_props(matrix_ring);
  }
}
