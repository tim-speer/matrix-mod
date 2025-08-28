#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  MatrixMod m = create_matrix(3, 3, 5, entries);
  MatrixMod row = get_matrix_row(m, 1);

  print_matrix_info(m);
  set_matrix_entry(m, 1, 2, 5);
  set_matrix_entry(m, 1, 1, 10);
  print_matrix_info(m);
  reduce_matrix(m);
  print_matrix_info(m);

  free_matrix(&m);
  free_matrix(&row);

  return EXIT_SUCCESS;

}
