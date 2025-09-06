#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"
#include "matrixprop.h"

int main(void) {

  MatrixList matrix_list = create_matrix_list(2, 2, 2);
  MatrixProp *props = create_matrix_prop_list(2, 2, 2);
  unsigned int num = num_matrices(2, 2, 2);
  calc_idempotents(matrix_list, props);

  for(unsigned int i = 0; i < num; i++) {
    print_matrix_prop(props[i]);
  }

  free_matrix_prop_list(props);

  return EXIT_SUCCESS;
}
