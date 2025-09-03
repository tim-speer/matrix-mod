#ifndef MATRIX_MOD_H
#define MATRIX_MOD_H

typedef struct { 
                 unsigned int rows;
                 unsigned int columns; 
                 unsigned int modulus; 
                 unsigned int *entries;
               } MatrixMod;

typedef struct {
                 unsigned int rows;
                 unsigned int columns;
                 unsigned int modulus;
                 MatrixMod *matrices;
               } MatrixList;

MatrixMod create_zero_matrix(unsigned int rows,
                             unsigned int columns,
                             unsigned int modulus);
MatrixMod create_matrix(unsigned int rows,
                        unsigned int columns,
                        unsigned int modulus,
                        unsigned int entries[rows * columns]);
MatrixMod create_reduced_matrix(unsigned int rows,
                                unsigned int columns,
                                unsigned int modulus,
                                unsigned int entries[rows * columns]);
MatrixList create_empty_matrix_list(unsigned int rows,
                                    unsigned int columns,
                                    unsigned int modulus);
void free_matrix(MatrixMod *matrix);
unsigned int matrix_size(MatrixMod matrix);
unsigned int num_matrices(unsigned int rows, 
                          unsigned int columns, 
                          unsigned int modulus);
unsigned int num_entries(unsigned int rows, unsigned int columns);
unsigned int *entry_address(MatrixMod matrix,
                            unsigned int row,
                            unsigned int column);
MatrixMod get_matrix_row(MatrixMod matrix, unsigned int row);
MatrixMod get_matrix_column(MatrixMod matrix, unsigned int column);
unsigned int get_matrix_entry(MatrixMod matrix, 
                              unsigned int row, 
                              unsigned int column);
void set_matrix_entry(MatrixMod matrix,
                      unsigned int row,
                      unsigned int columns,
                      unsigned int value);
void set_matrix_entries(MatrixMod matrix,
                        unsigned int entries[matrix.rows * matrix.columns]);
void print_matrix(MatrixMod matrix);
void print_matrix_info(MatrixMod matrix);
void reduce_matrix_entry(MatrixMod matrix,
                         unsigned int row,
                         unsigned int column);
void reduce_matrix(MatrixMod matrix);
unsigned int inner_product(MatrixMod row, MatrixMod column);
MatrixMod multiply_matrices(MatrixMod left, MatrixMod right);
MatrixMod square_matrix(MatrixMod matrix);
MatrixMod reduce_multiply_matrices(MatrixMod left, MatrixMod right);
unsigned int calc_digit(unsigned int modulus,
                        unsigned int position,
                        unsigned int value);
MatrixMod gen_matrix(unsigned int rows,
                     unsigned int columns,
                     unsigned int modulus,
                     unsigned int value);

#endif
