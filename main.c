#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"

int main(void) {

  unsigned int entries[9] = {10, 9, 0, 0, 1, 0, 0, 0, 1};
  MatrixMod m = create_matrix(3, 3, 5, entries);
  MatrixMod m_red = create_reduced_matrix(3, 3, 5, entries);
  MatrixMod row = get_matrix_row(m_red, 2);
  MatrixMod column = get_matrix_column(m_red, 2);

  print_matrix_info(m_red);
  print_matrix_info(row);
  print_matrix_info(column);
  printf("\n%u", inner_product(row, column));

  free_matrix(&m_red);
  free_matrix(&row);
  free_matrix(&column);
  free_matrix(&m);

  return EXIT_SUCCESS;

}
