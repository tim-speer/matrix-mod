#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"
#include "matrixprop.h"
#include "matrixring.h"

unsigned int get_matrix_ring_modulus(void) {
  unsigned int modulus;

  printf("\nEnter Matrix Modulus: ");
  int n = scanf("%u", &modulus);
  if (n != 1 || modulus < 2) {
    printf("Failed to load matrix ring. Modulus should be at least 2.\n");
    modulus = 0;
  }

  return modulus;
}

unsigned int get_matrix_ring_dim(void) {
  unsigned int dim;
  
  printf("\nEnter Matrix Dimensions: ");
  int n = scanf("%u", &dim);
  if (n != 1 || dim < 2) {
    printf("Failed to load matrix ring. Dimensions should be at least 2.\n");
    dim = 0;
  }

  return dim;
}

MatrixRing load_matrix_ring(void) {
  printf("\n*******************");
  printf("\nLoading Matrix Ring");
  printf("\n*******************");

  MatrixRing matrix_ring;
  unsigned int dim = get_matrix_ring_dim();
  if (dim == 0) {
    matrix_ring = create_matrix_ring(2, 2);
    return matrix_ring;
  }
 
  unsigned int modulus = get_matrix_ring_modulus();
  if (modulus == 0) {
    matrix_ring = create_matrix_ring(2, 2);
  } else {
    matrix_ring = create_matrix_ring(dim, modulus);
  }

  return matrix_ring;
}

void display_menu(void) {
  char in = '?';
  MatrixRing matrix_ring = create_matrix_ring(2, 2);

  while(in != 'q') {
    printf("\n********************");
    printf("\n(l) Load Matrix Ring");
    printf("\n(p) Print Matrix Ring");
    printf("\n(q) Quit");
    printf("\n********************");
    printf("\nEnter Choice: ");
    scanf("%s", &in);
    switch(in) {
      case 'l':
        matrix_ring = load_matrix_ring();
      case 'p':
        print_matrix_ring(matrix_ring);      
      case 'q':
        break;
      default:
        printf("!!!Invalid Choice!!!\n");
    }
  }
}

int main(void) {
  display_menu();
  return EXIT_SUCCESS;
}
