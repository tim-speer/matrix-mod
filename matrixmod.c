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

void free_matrix(MatrixMod *matrix) {
  free(matrix->entries);
  matrix->entries = NULL;
}

unsigned int num_matrices(unsigned int rows, 
                          unsigned int columns, 
                          unsigned int modulus) {
  return (unsigned int)pow(modulus, rows * columns); 
}

unsigned int *entry_address(MatrixMod matrix,
                            unsigned int row,
                            unsigned int column) {
  check_matrix_dim(matrix, row, column);
  return matrix.entries + (row - 1) * matrix.columns + (column - 1);
}

MatrixMod get_matrix_row(MatrixMod matrix, unsigned int row) {
  check_matrix_row(matrix, row);
  unsigned int *row_p = entry_address(matrix, row, 1); 
  return create_matrix(1, matrix.columns, matrix.modulus, row_p);
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
  for (unsigned int i = 0; i < (matrix.rows * matrix.columns); i++) {
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

