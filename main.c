#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int num = num_matrices(2, 2, 3);
  MatrixList matrix_list = create_matrix_list(2, 2, 3);
  
  for (unsigned int i = 0; i < num; i++) {
    print_matrix_info(matrix_list.matrices[i]);
    free_matrix(&matrix_list.matrices[i]);
  }

  free(matrix_list.matrices);

  return EXIT_SUCCESS;
}
