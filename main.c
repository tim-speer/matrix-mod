#include <stdlib.h>
#include <stdio.h>
#include "matrixmod.h"
#include "matrixprop.h"
#include "matrixring.h"

unsigned int get_matrix_ring_dim(void) {
  unsigned int dim;
  
  printf("\nEnter Matrix Dimensions: ");
  int n = scanf("%u", &dim);
  if (n == 0 || dim < 2) {
    printf("Failed to load matrix ring. Dimensions should be at least 2.\n");
    dim = 0;
  }

  return dim;
}

MatrixRing load_matrix_ring(void) {
  MatrixRing matrix_ring;
  printf("\n*******************");
  printf("\nLoading Matrix Ring");
  printf("\n*******************");
  unsigned int dim = get_matrix_ring_dim(); 

  return matrix_ring;
}

void display_menu(void) {
  char in = '?';
  MatrixRing matrix_ring;

  while(in != 'q') {
    printf("\n********************");
    printf("\n(l) Load Matrix Ring");
    printf("\n(q) Quit");
    printf("\n********************");
    printf("\nEnter Choice: ");
    scanf("%s", &in);
    switch(in) {
      case 'l':
        matrix_ring = load_matrix_ring();      
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
