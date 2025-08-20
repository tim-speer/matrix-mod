#ifndef MATRIX_MOD_H
#define MATRIX_MOD_H

typedef struct { 
                 const unsigned int rows;
		 const unsigned int columns; 
                 const unsigned int modulus; 
                 unsigned int *entries;
               } MatrixMod;

MatrixMod create_matrix(const unsigned int rows,
			const unsigned int columns, 
                        const unsigned int modulus, 
                        unsigned int entries[rows * columns]);
unsigned int num_matrices(unsigned int rows, 
                          unsigned int columns, 
                          unsigned int modulus);
unsigned int *get_matrix_row(MatrixMod matrix, unsigned int row);
unsigned int get_matrix_entry(MatrixMod matrix, 
                              unsigned int row, 
                              unsigned int column);

#endif
