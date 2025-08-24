#include <stdio.h>
#include <stdlib.h>
#include "checks.h"

void check_matrix_row(MatrixMod matrix, unsigned int row) {
  if (row < 1 || row > matrix.rows) {
    printf("Error: Invalid row number");
    exit(EXIT_FAILURE);
  }
}

void check_matrix_column(MatrixMod matrix, unsigned int column) {
  if (column < 1 || column > matrix.columns) {
    printf("Error: Invalid column number");
    exit(EXIT_FAILURE);
  }
}

void check_matrix_dim(MatrixMod matrix, 
                      unsigned int row,
                      unsigned int column) {
  check_matrix_row(matrix, row);
  check_matrix_column(matrix, column);
}

void check_positive(unsigned int num) {
  if (num == 0) {
    printf("Error: Need a positive integer");
    exit(EXIT_FAILURE);
  }
}
