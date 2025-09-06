#include <stdio.h>
#include <stdlib.h>
#include "matrixprop.h"
#include "checks.h"

MatrixProp *__alloc_matrix_prop_list(unsigned int rows,
                                     unsigned int columns,
                                     unsigned int modulus) {
  check_matrix_params(rows, columns, modulus);
  unsigned int num = num_matrices(rows, columns, modulus);
  MatrixProp *props = calloc(num, sizeof(MatrixProp));

  if (props == NULL) {
    printf("Could not allocate memory for MatrixProp list");
    exit(EXIT_FAILURE);
  }

  return props;
}

MatrixProp create_matrix_prop(void) {
  MatrixProp prop = { -1, -1, -1, -1};
  return prop;
}

MatrixProp *create_matrix_prop_list(unsigned int rows,
                                     unsigned int columns,
                                     unsigned int modulus) {
  MatrixProp *props = __alloc_matrix_prop_list(rows, columns, modulus);
  unsigned int num = num_matrices(rows, columns, modulus);

  for (unsigned int i = 0; i < num; i++) {
    props[i] = create_matrix_prop();
  }

  return props;
}

void free_matrix_prop_list(MatrixProp *props) {
  free(props);
  props = NULL;
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

void calc_idempotents(MatrixList matrix_list, MatrixProp *props) {
  printf("\nCalculating Idempotents\n");
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);

  for (unsigned int i = 0; i < num; i++) {
    if ((i + 1) % 500  == 0) {
      printf("%u/%u\n", i + 1, num);
    }
    if (is_idempotent(matrix_list.matrices[i])) {
      props[i].idempotent = 1; 
    }
    else {
      props[i]. idempotent = 0;
    }
  }
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

void calc_units(MatrixList matrix_list, MatrixProp *props) {
  printf("\nCalculating Units\n");
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);

  for (unsigned int i = 0; i < num; i++) {
    if ((i + 1) % 500 == 0) {
      printf("%u/%u\n", i + 1, num);
    }
    if (is_unit(matrix_list.matrices[i], matrix_list)) {
      props[i].unit = 1;
    } else {
      props[i].unit = 0;
    }
  }
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
  printf("N-Torsion Clean Decomposition = %d\n", prop.n_torsion_clean);
  printf("Strongly N-Torsion Clean Decomposition = %d\n", prop.strongly_n_torsion_clean);
}

void __n_tor_decomp(MatrixList matrix_list, MatrixProp *props, unsigned int i, unsigned int j) {
  MatrixMod sum = add_matrices(matrix_list.matrices[i], matrix_list.matrices[j]);
  unsigned int num = num_matrices(matrix_list.rows, matrix_list.columns, matrix_list.modulus);
  for (unsigned int k = 0; k < num; k++) {
    if (matrices_equal(sum, matrix_list.matrices[k])) {
      props[k].n_torsion_clean = 1;
      break;
    }
  }
  free_matrix(&sum);
}

void __n_tor_unit(MatrixList matrix_list, MatrixProp *props, unsigned int i, int n) {
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);
  for (unsigned int j = 0; j < num; j++) {
    if (props[j].unit == 1) {
      MatrixMod prod = power_matrix(matrix_list.matrices[j], n);
      MatrixMod id = identity_matrix(matrix_list.rows, matrix_list.modulus);
      if (matrices_equal(prod, id) == 1) {
        __n_tor_decomp(matrix_list, props, i, j);
      }
      free_matrix(&prod);
      free_matrix(&id);
    }
  }
}

void __n_tor_idem(MatrixList matrix_list, MatrixProp *props, int n) {
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);
  for (unsigned int i = 0; i < num; i++) {
    if (props[i].idempotent == 1) {
      __n_tor_unit(matrix_list, props, i, n);
    }
  }
}

void __strg_n_tor_decomp(MatrixList matrix_list, MatrixProp *props, unsigned int i, unsigned int j) {
  MatrixMod sum = add_matrices(matrix_list.matrices[i], matrix_list.matrices[j]);
  unsigned int num = num_matrices(matrix_list.rows, matrix_list.columns, matrix_list.modulus);
  for (unsigned int k = 0; k < num; k++) {
    if (matrices_equal(sum, matrix_list.matrices[k])) {
      props[k].strongly_n_torsion_clean = 1;
      break;
    }
  }
  free_matrix(&sum);
}

void __strg_n_tor_unit(MatrixList matrix_list, MatrixProp *props, unsigned int i, int n) {
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);
  for (unsigned int j = 0; j < num; j++) {
    if (props[j].unit == 1) {
      MatrixMod prod = power_matrix(matrix_list.matrices[j], n);
      MatrixMod id = identity_matrix(matrix_list.rows, matrix_list.modulus);
      MatrixMod left = multiply_matrices(matrix_list.matrices[i], matrix_list.matrices[j]);
      MatrixMod right = multiply_matrices(matrix_list.matrices[j], matrix_list.matrices[i]);
 
      if (matrices_equal(prod, id) == 1 && matrices_equal(left, right)) {
        __strg_n_tor_decomp(matrix_list, props, i, j);
      }

      free_matrix(&prod);
      free_matrix(&id);
      free_matrix(&left);
      free_matrix(&right);
    }
  }
}

void __strg_n_tor_idem(MatrixList matrix_list, MatrixProp *props, int n) {
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);
  for (unsigned int i = 0; i < num; i++) {
    if (props[i].idempotent == 1) {
      __strg_n_tor_unit(matrix_list, props, i, n);
    }
  }
}

int calc_n_torsion_clean(MatrixList matrix_list, 
                         MatrixProp *props, 
                         int n) {
  printf("\nCalculating N-Torsion Clean Decompositions n = %d", n);
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);
  for (unsigned int i = 0; i < num; i++) {
    props[i].n_torsion_clean = 0;
  }
  __n_tor_idem(matrix_list, props, n);

  for (unsigned int i = 0; i < num; i++) {
    if (props[i].n_torsion_clean != 1) {
      printf("\nFailure");
      return 0;
    }
  }
  printf("\n********Success********");
  return 1;
}

int calc_strongly_n_torsion_clean(MatrixList matrix_list,
                                  MatrixProp *props,
                                  int n) {
  printf("\nCalculating Strongly N-Torsion Clean Decompositions n = %d", n);
  unsigned int num = num_matrices(matrix_list.rows,
                                  matrix_list.columns,
                                  matrix_list.modulus);
  for (unsigned int i = 0; i < num; i++) {
    props[i].strongly_n_torsion_clean = 0;
  }

  __strg_n_tor_idem(matrix_list, props, n);

  for (unsigned int i = 0; i < num; i++) {
    if (props[i].strongly_n_torsion_clean != 1) {
      printf("\nFailure");
      return 0;
    }
  }

  printf("\n********Success********");
  return 1;
}
