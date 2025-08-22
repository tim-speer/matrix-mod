#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  MatrixMod m = create_matrix(3, 3, 2, entries);
  MatrixMod row = get_matrix_row(m, 1);

  print_matrix_info(m);
  print_matrix_info(row);

  set_matrix_entry(m, 1, 2, 5);
  print_matrix_info(m);
  print_matrix_info(row);

  MatrixMod new_row = get_matrix_row(m, 1);
  print_matrix_info(new_row);

  free_matrix(&new_row);
  free_matrix(&m);
  free_matrix(&row);

  return EXIT_SUCCESS;

}
