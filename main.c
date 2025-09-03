#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int num = num_matrices(2, 2, 3);
  MatrixList matrix_list = create_matrix_list(2, 2, 3);
  free_matrix_list(&matrix_list);
  return EXIT_SUCCESS;
}
