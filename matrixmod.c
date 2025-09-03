#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrixmod.h"
#include "checks.h"

unsigned int *__alloc_matrix(unsigned int rows, unsigned int columns) {
  check_positive(rows);
  check_positive(columns);

  unsigned int size = rows * columns;
  unsigned int *entries = calloc(size, sizeof(unsigned int)); 

  if (entries == NULL) {     
    printf("Could not allocate memory for matrix.");
    exit(EXIT_FAILURE);
  }     

  return entries;
}

MatrixMod *__alloc_matrices(unsigned int rows, 
                            unsigned int columns, 
                            unsigned int modulus) {
  check_matrix_params(rows, columns, modulus);
  
  unsigned int num = num_matrices(rows, columns, modulus);
  MatrixMod *matrices = calloc(num, sizeof(MatrixMod));

  if (matrices == NULL) {
    printf("Could not allocate memory for matrices.");
    exit(EXIT_FAILURE);
  }

  return matrices;
}

MatrixMod create_zero_matrix(unsigned int rows,
                             unsigned int columns,      
                             unsigned int modulus) {
  check_modulus(modulus);
  unsigned int *entries = __alloc_matrix(rows, columns);
  MatrixMod matrix = { rows, columns, modulus, entries };
  return matrix;
}

MatrixMod create_matrix(unsigned int rows,
                        unsigned int columns,
                        unsigned int modulus,
                        unsigned int entries[rows * columns]) {
  MatrixMod matrix = create_zero_matrix(rows, columns, modulus);
  set_matrix_entries(matrix, entries);
  return matrix;
}

MatrixMod create_reduced_matrix(unsigned int rows,
                                unsigned int columns,
                                unsigned int modulus,
                                unsigned int entries[rows * columns]) {
  MatrixMod matrix = create_matrix(rows, columns, modulus, entries);
  reduce_matrix(matrix);
  return matrix;
}

void free_matrix(MatrixMod *matrix) {
  free(matrix->entries);
  matrix->entries = NULL;
}

unsigned int matrix_size(MatrixMod matrix) {
  return matrix.rows * matrix.columns;
}

/*************************************************************
Returns the number of matrices with dimensions rows by columns 
with entries from the ring of integers mod the parameter 
modulus. This number is given by the formula:

number of matrices = modulus ^ (rows * columns) 
 
*************************************************************/
unsigned int num_matrices(unsigned int rows, 
                          unsigned int columns, 
                          unsigned int modulus) {
  check_matrix_params(rows, columns, modulus);
  unsigned int num = 1;
  for (unsigned int i = 1; i <= num_entries(rows, columns); i++) {
    num *= modulus;
  }

  return num;
}

/*************************************************************
Caculates the number of entries in a matrix with dimensions
of rows and columns.
*************************************************************/
unsigned int num_entries(unsigned int rows,
                         unsigned int columns) {
  check_matrix_params(rows, columns, 2);
  return rows * columns;   
}

unsigned int *entry_address(MatrixMod matrix,
                            unsigned int row,
                            unsigned int column) {
  check_matrix_dim(matrix, row, column);
  return matrix.entries + (row - 1) * matrix.columns + (column - 1);
}

MatrixMod get_matrix_row(MatrixMod matrix, unsigned int row) {
  unsigned int *row_p = entry_address(matrix, row, 1); 
  return create_matrix(1, matrix.columns, matrix.modulus, row_p);
}

MatrixMod get_matrix_column(MatrixMod matrix, unsigned int column){
  MatrixMod new_column = create_zero_matrix(matrix.rows, 1, matrix.modulus);
  for (unsigned int i = 1; i <= matrix.rows; i++) {
    unsigned int value = get_matrix_entry(matrix, i, column);
    set_matrix_entry(new_column, i, 1, value);     
  }

  return new_column;

}

unsigned int get_matrix_entry(MatrixMod matrix, 
                              unsigned int row, 
                              unsigned int column) {
  return *entry_address(matrix, row, column);
}

void set_matrix_entry(MatrixMod matrix,
                      unsigned int row,
                      unsigned int column,
                      unsigned int value) {
  unsigned int *entry_p = entry_address(matrix, row, column);
  *(entry_p) = value;   
}

void set_matrix_entries(MatrixMod matrix,
                        unsigned int entries[matrix.rows * matrix.columns]) {
  unsigned int index = 0;
  for (unsigned int row = 1; row <= matrix.rows; row++) {
    for (unsigned int column = 1; column <= matrix.columns; column++) {
      set_matrix_entry(matrix, row, column, entries[index]);
      index++;
    }
  }
}

void print_matrix(MatrixMod matrix) {
  if (!matrix.entries) {
    printf("Error: Trying to print a matrix will NULL entries");
    exit(EXIT_FAILURE);
  }
  
  for (unsigned int i = 0; i < matrix_size(matrix); i++) {
    printf("%u", *(matrix.entries + i));
    if ((i + 1) % matrix.columns == 0) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
}

void print_matrix_info(MatrixMod matrix) {
  printf("rows = %u\n", matrix.rows);
  printf("columns = %u\n", matrix.columns);
  printf("modulus = %u\n", matrix.modulus); 
  print_matrix(matrix);
}

void reduce_matrix_entry(MatrixMod matrix, 
                         unsigned int row, 
                         unsigned int column) {
  unsigned int *entry_p = entry_address(matrix, row, column);
  *(entry_p) = (*(entry_p)) % matrix.modulus;
}

void reduce_matrix(MatrixMod matrix) {
  for (unsigned int i = 0; i < matrix_size(matrix); i++) {
    unsigned int row = i / matrix.columns + 1;
    unsigned int column = i % matrix.columns + 1;
    reduce_matrix_entry(matrix, row, column);
  }
}

unsigned int inner_product(MatrixMod row, MatrixMod column) {
  unsigned int product = 0;
  for (unsigned int i = 1; i <= row.columns; i++) {
    product += get_matrix_entry(row, 1, i) * 
               get_matrix_entry(column, i, 1);
  }

  return product;  
}

MatrixMod multiply_matrices(MatrixMod left, MatrixMod right) {
  check_multiply_dim(left, right);
  MatrixMod product = create_zero_matrix(left.rows, 
                                         right.columns, 
                                         left.modulus);

  for (unsigned int i = 1; i <= left.rows; i++) {
    MatrixMod row = get_matrix_row(left, i);
    for (unsigned int j = 1; j <= right.columns; j++) {
      MatrixMod column = get_matrix_column(right, j);
      set_matrix_entry(product, i, j, inner_product(row, column));
      free_matrix(&column);
    }
    free_matrix(&row);
  }

  return product;
}

MatrixMod square_matrix(MatrixMod matrix) {
  return multiply_matrices(matrix, matrix);
}

MatrixMod reduce_multiply_matrices(MatrixMod left, MatrixMod right) {
  MatrixMod product = multiply_matrices(left, right);
  reduce_matrix(product);
  return product;
}

unsigned int __power(unsigned int modulus, 
                     unsigned int exp) {
  unsigned int power = 1;
  for (unsigned int i = 1; i <= exp; i++) {
    power *= modulus;
  }

  return power;
}

unsigned int calc_digit(unsigned int modulus,
                        unsigned int position,
                        unsigned int value) {
  unsigned int power = __power(modulus, position);
  unsigned int digit = 0;

  while (value >= power) {
    value -= power;
    digit++;      
  }

  return digit;
}

MatrixMod gen_matrix(unsigned int rows,
                     unsigned int columns,
                     unsigned int modulus,
                     unsigned int value) {
  MatrixMod matrix = create_zero_matrix(rows, columns, modulus);
  unsigned int num = num_entries(rows, columns);
  unsigned int digit = 0;  
  unsigned int position = num - 1;

  for (unsigned int i = 0; i < num; i++) {
    digit = calc_digit(modulus, position, value);
    matrix.entries[i] = digit;
    value -= digit * __power(modulus, position);
    position--;
  }

  return matrix;
}
