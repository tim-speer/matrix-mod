#ifndef MATRIX_MOD_H
#define MATRIX_MOD_H

typedef struct { 
                 const unsigned int size; 
                 const unsigned int modulus; 
                 unsigned int *entries;
               } MatrixMod;

MatrixMod create_matrix(const unsigned int size, 
                        const unsigned int modulus, 
                        unsigned int entries[size * size]);
unsigned int num_matrices(unsigned int size, unsigned int modulus);
unsigned int get_matrix_entry(MatrixMod matrix, 
                              unsigned int row, 
                              unsigned int column);
unsigned int *get_matrix_row(MatrixMod matrix, unsigned int row);

#endif
