#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"
#include "matrixprop.h"

int main(void) {

  MatrixList matrix_list = create_matrix_list(2, 2, 2);
  unsigned int num = num_matrices(2, 2, 2);

  for (unsigned int i = 0; i < num; i++) {
    MatrixProp prop = create_matrix_prop();
    prop.idempotent = is_idempotent(matrix_list.matrices[i]);
    prop.unit = is_unit(matrix_list.matrices[i], matrix_list);
    print_matrix_info(matrix_list.matrices[i]);
    print_matrix_prop(prop);
  }

  free_matrix_list(&matrix_list);

  return EXIT_SUCCESS;
}
