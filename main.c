#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries[4] = {1, 0, 0, 1};
  MatrixMod m = create_matrix(2, 2, entries);
  printf("Entry (1, 1) = %u", get_matrix_entry(m, 1, 1));

  return EXIT_SUCCESS;

}
