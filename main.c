#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sqmatrix.h"

# define SIZE 10
# define RANGE 5

int main() {
    srand(time(NULL));
    
    int **A = malloc_sq_matrix(SIZE);
    int **B = malloc_sq_matrix(SIZE);
    int **C = malloc_sq_matrix(SIZE);
    
    rand_init_sq_matrix(A, RANGE);
    rand_init_sq_matrix(B, RANGE);
    rand_init_sq_matrix(C, 1);

    print_sq_matrix(A, "A");
    print_sq_matrix(B, "B");
    print_sq_matrix(C, "C");

    mult_sq_matrices(A, B, C);

    print_sq_matrix(C, "C");

    free_sq_matrix(A);
    free_sq_matrix(B);
    free_sq_matrix(C);
    return 0; 
}