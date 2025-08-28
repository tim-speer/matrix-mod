#ifndef MATRIX_MOD_H
#define MATRIX_MOD_H

typedef struct { 
                 const unsigned int rows;
                 const unsigned int columns; 
                 const unsigned int modulus; 
                 unsigned int *entries;
               } MatrixMod;

MatrixMod create_zero_matrix(unsigned int rows,
                             unsigned int columns,
                             unsigned int modulus);
MatrixMod create_matrix(unsigned int rows,
                         unsigned int columns,
                         unsigned int modulus,
                         unsigned int entries[rows * columns]);
void free_matrix(MatrixMod *matrix);
unsigned int matrix_size(MatrixMod matrix);
unsigned int num_matrices(unsigned int rows, 
                          unsigned int columns, 
                          unsigned int modulus);
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

#endif
