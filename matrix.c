#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int** malloc_square_matrix(size_t size) {
    int **matrix = (int **)malloc((size + 1) * sizeof(int *));
    if (matrix == NULL) {
        perror("couldn't allocate memory for matrix row!");
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
        if (matrix[i] == NULL) {
            perror("couldn't allocate memory for matrix column! dellocating previous columns...");
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL; 
        }
    }
    matrix[size] = NULL;
    return matrix; 
}

void free_square_matrix(int **matrix) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void rand_init_square_matrix(int **matrix, size_t range) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        for (size_t j = 0; matrix[j] != NULL; j++) {
            matrix[i][j] = rand() % range;
        }
    }
}