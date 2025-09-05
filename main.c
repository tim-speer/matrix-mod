#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  MatrixMod iden = identity_matrix(4, 2);
  print_matrix_info(iden);
  free_matrix(&iden);
  return EXIT_SUCCESS;
}
