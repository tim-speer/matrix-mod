#include <stdio.h>
#include <stdlib.h>
#include "checks.h"

void check_matrix_row(MatrixMod matrix, unsigned int row) {
  if (row < 1 || row > matrix.rows) {
    printf("Error: Invalid row number");
    exit(EXIT_FAILURE);
  }
}
