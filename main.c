#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix.h"

# define SIZE 10
# define RANGE 100

int main() {
    srand(time(NULL));
    
    int **A = malloc_square_matrix(SIZE);
    int **B = malloc_square_matrix(SIZE);
    rand_init_square_matrix(A, RANGE);
    rand_init_square_matrix(B, RANGE);

    printf("Matrix A contents:\n");
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    printf("Matrix B contents:\n");
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    free_square_matrix(A);
    free_square_matrix(B);
    return 0; 
}