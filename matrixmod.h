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

#endif
