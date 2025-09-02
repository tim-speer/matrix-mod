#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries_m[4] = {10, 9, 0, 1};
  unsigned int entries_n[6] = {1, 1, 0, 0, 1, 1};
  MatrixMod m = create_matrix(2, 2, 5, entries_m);
  MatrixMod n = create_matrix(2, 3, 5, entries_n);
  MatrixMod p = multiply_matrices(m, n);
  MatrixMod p_red = reduce_multiply_matrices(m, n);
 
  print_matrix_info(m);
  print_matrix_info(n);
  print_matrix_info(p);
  print_matrix_info(p_red);
  print_matrix_info(square_matrix(m));

  free_matrix(&p);
  free_matrix(&p_red);
  free_matrix(&m);
  free_matrix(&n);

  printf("\n\n%u", largest_digit_position(16, 2));

  return EXIT_SUCCESS;

}
