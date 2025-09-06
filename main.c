#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"
#include "matrixprop.h"
#include "matrixring.h"

int main(void) {

  MatrixRing matrix_ring = create_matrix_ring(2, 2, 2);
  calc_matrix_ring_props(&matrix_ring);
  print_matrix_ring(matrix_ring);
  free_matrix_ring(&matrix_ring);
  return EXIT_SUCCESS;
}
