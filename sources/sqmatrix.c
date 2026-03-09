/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Dynamically creates a matrix using pointers of pointers of integers. 
int** malloc_sq_matrix(size_t size) {
    int **matrix = (int **)malloc((size + 1) * sizeof(int *));
    int *row = (int *)malloc(size * size * sizeof(int));
    if (matrix == NULL) {
        perror("couldn't allocate memory for matrix row!");
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        matrix[i] = &row[i * size];
        if (matrix[i] == NULL) {
            perror("couldn't allocate memory for matrix column! dellocating previous columns...");
            for (size_t j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL; 
        }
    }
    // Sentinel value. Important for iterating through entries in matrix and knowing when to terminate loops. 
    matrix[size] = NULL;
    return matrix; 
}

void free_sq_matrix(int **matrix) {
    free(matrix[0]);
    free(matrix);
}

// For matrix initalization, generate random integers in the entries. 
void rand_init_sq_matrix(int **matrix, size_t range) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        for (size_t j = 0; matrix[j] != NULL; j++) {
            matrix[i][j] = rand() % range;
        }
    }
}

// Basic matrix multiplication function. Requires an initialized product matrix to store entries.
void mult_sq_matrices(int **pre_matrix, int **post_matrix, int **prod_matrix) {
    for (size_t i = 0; prod_matrix[i] != NULL; i++) {
        for (size_t j = 0; prod_matrix[j] != NULL; j++) {
            for (size_t k = 0; prod_matrix[k] != NULL; k++) {
                prod_matrix[i][j] += pre_matrix[i][k] * post_matrix[k][j];
            }
        }
    }
}

// Similar to matrix multiplication except here we are performing row vector multiplication with a square matrix.
void mult_sq_matrices_by_row(int row, int **pre_matrix, int **post_matrix, int **prod_matrix) {
    for (size_t j = 0; prod_matrix[j] != NULL; j++) {
        int sum = 0;
        for (size_t k = 0; prod_matrix[k] != NULL; k++) {
            sum += pre_matrix[row][k] * post_matrix[k][j];
        }
        prod_matrix[row][j] = sum;
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
    printf("\n");
}

// Check to see if pre_matrix and post_matrix have the same entires and are the same matrix or not. 
bool same_matrix(int **pre_matrix, int **post_matrix) {
    for (size_t i = 0; pre_matrix[i] != NULL; i++) {
        for (size_t j = 0; pre_matrix[j] != NULL; j++) {
            if (pre_matrix[i][j] != post_matrix[i][j]) return false;
        }
    }
    return true; 
}