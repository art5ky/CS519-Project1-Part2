#include <stdlib.h>
#include <stdio.h>
#include "sqmatrix.h"

int** malloc_sq_matrix(size_t size) {
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

void free_sq_matrix(int **matrix) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void rand_init_sq_matrix(int **matrix, size_t range) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        for (size_t j = 0; matrix[j] != NULL; j++) {
            matrix[i][j] = rand() % range;
        }
    }
}

void mult_sq_matrices(int **pre_matrix, int **post_matrix, int **prod_matrix) {
    for (size_t i = 0; prod_matrix[i] != NULL; i++) {
        for (size_t j = 0; prod_matrix[j] != NULL; j++) {
            for (size_t k = 0; prod_matrix[k] != NULL; k++) {
                prod_matrix[i][j] += pre_matrix[i][k] * post_matrix[k][j];
            }
        }
    }
}

void print_sq_matrix(int **matrix, const char *name) {
    printf("\nMatrix %s entries:\n", name);
    for (size_t i = 0; matrix[i] != NULL; i++) {
        for (size_t j = 0; matrix[j] != NULL; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}
