#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  MatrixList matrix_list = create_matrix_list(2, 2, 2);
  unsigned int num = num_matrices(2, 2, 2);
  for (unsigned int i = 0; i < num; i++) {
    print_matrix_info(matrix_list.matrices[i]);
    printf("Is Idempotent = %d\n", is_idempotent(matrix_list.matrices[i]));
  }
  return EXIT_SUCCESS;
}
