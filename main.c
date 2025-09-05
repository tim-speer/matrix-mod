#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  MatrixMod iden = identity_matrix(2, 2);
  unsigned int entries[4] = { 3, 0, 0, 3 };
  MatrixMod iden2 = create_matrix(2, 2, 2, entries);

  printf("Equal = %d\n", matrices_equal(iden, iden2));
  print_matrix_info(iden);
  print_matrix_info(iden2);

  free_matrix(&iden);
  free_matrix(&iden2);
  return EXIT_SUCCESS;
}
