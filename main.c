#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries_m[4] = {10, 9, 0, 1};
  unsigned int entries_n[6] = {1, 1, 0, 0, 1, 1};
  MatrixMod m = create_matrix(2, 2, 5, entries_m);
  MatrixMod n = create_matrix(2, 3, 5, entries_n);
  
  print_matrix_info(m);
  print_matrix_info(n);
  print_matrix_info(multiply_matrices(m, n));

  free_matrix(&m);
  free_matrix(&n);

  return EXIT_SUCCESS;

}
