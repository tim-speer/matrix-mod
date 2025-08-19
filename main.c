#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  MatrixMod m = create_matrix(3, 2, entries);
  printf("Row 2\n");
  unsigned int *row = get_matrix_row(m, 2);
  for (unsigned int i = 0; i < m.size; i++) {
    printf("%u ", *(row + i));
  }

  return EXIT_SUCCESS;

}
