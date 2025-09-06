#include <stdio.h>
#include "matrixprop.h"
#include "checks.h"

MatrixProp create_matrix_prop(void) {
  MatrixProp prop = { -1, -1 };
  return prop;
}

int matrices_equal(MatrixMod left, MatrixMod right) {
  check_matrices_equal(left, right);
  unsigned int num = num_entries(left.rows, left.columns);
  reduce_matrix(left);
  reduce_matrix(right);

  for (unsigned int i = 0; i < num; i++) {
    if (left.entries[i] != right.entries[i]) {
      return 0;
    }
  }

  return 1;
}

int is_idempotent(MatrixMod matrix) {
  if (matrices_equal(matrix, square_matrix(matrix))) {
    return 1;
  }

  return 0;
}

int is_inverse(MatrixMod matrix, MatrixMod inverse) {
  check_is_square(matrix);
  check_is_square(inverse);

  MatrixMod right_mul = reduce_multiply_matrices(matrix, inverse);
  MatrixMod left_mul = reduce_multiply_matrices(inverse, matrix);
  MatrixMod id = identity_matrix(matrix.rows, matrix.modulus);

  if (matrices_equal(right_mul, id) && matrices_equal(left_mul, id)) {
    return 1;
  }
 
  free_matrix(&right_mul);
  free_matrix(&left_mul);
  free_matrix(&id);

  return 0; 
}

int is_unit(MatrixMod matrix, MatrixList matrix_list) {
  unsigned int num = num_matrices(matrix.rows, matrix.columns, matrix.modulus);
  
  for (unsigned int i = 0; i < num; i++) {
    if (is_inverse(matrix, matrix_list.matrices[i])) {
      return 1;
    }
  }

  return 0;
}

void print_matrix_prop(MatrixProp prop) {
  printf("Idempotent = %d\n", prop.idempotent);
  printf("Unit = %d\n", prop.unit);
}
