#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int num = num_matrices(2, 2, 3);
  MatrixMod *matrices;

  for (unsigned int i = 0; i < num; i++) {
    matrices[i] = gen_matrix(2, 2, 3, i);
    print_matrix_info(matrices[i]);
    free_matrix(&matrices[i]);
  }

  return EXIT_SUCCESS;
}
