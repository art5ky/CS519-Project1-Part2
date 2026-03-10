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
    if (matrix == NULL || row == NULL) {
        perror("couldn't allocate memory for matrix or row!");
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        matrix[i] = &row[i * size];
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
void rand_init_sq_matrix(int **matrix) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        for (size_t j = 0; matrix[j] != NULL; j++) {
            matrix[i][j] = rand();
        }
    }
}

void zero_init_sq_matrix(int **matrix) {
    for (size_t i = 0; matrix[i] != NULL; i++) {
        for (size_t j = 0; matrix[j] != NULL; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Basic matrix multiplication function. Requires an initialized product matrix to store entries.
void mult_sq_matrices_full(int **pre_matrix, int **post_matrix, int **prod_matrix) {
    for (size_t i = 0; prod_matrix[i] != NULL; i++) {
        for (size_t j = 0; prod_matrix[j] != NULL; j++) {
            for (size_t k = 0; prod_matrix[k] != NULL; k++) {
                prod_matrix[i][j] += pre_matrix[i][k] * post_matrix[k][j];
            }
        }
    }
}

// Similar to mult_sq_matrices, except we are passing the row index as a parameter for pre_matrix. 
void mult_sq_matrices_row(int row, int **pre_matrix, int **post_matrix, int **prod_matrix) {
    for (size_t j = 0; prod_matrix[j] != NULL; j++) {
        int sum = 0;
        for (size_t k = 0; prod_matrix[k] != NULL; k++) {
            sum += pre_matrix[row][k] * post_matrix[k][j];
        }
        prod_matrix[row][j] = sum;
    }
}

void mult_sq_matrix_vec(int **matrix, int *post_vec, int *prod_vec) {
    for (size_t j = 0; matrix[j] != NULL; j++) {
        int sum = 0;
        for (size_t k = 0; matrix[k] != NULL; k++) {
            sum += matrix[j][k] * post_vec[k];
        }
        prod_vec[j] = sum;
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
bool same_matrix(int **A, int **B) {
    for (size_t i = 0; A[i] != NULL; i++) {
        for (size_t j = 0; A[j] != NULL; j++) {
            if (A[i][j] != B[i][j]) return false;
        }
    }
    return true; 
}

// Using Frievalds algorithm for checking matrix multiplication for MATRIX_SIZE > 2000.
bool frievalds_verify(int **A, int **B, int **C, size_t size) {
    int *r = (int *)malloc(size * sizeof(int));
    int *B_r = (int *)malloc(size * sizeof(int));
    int *C_r = (int *)malloc(size * sizeof(int));
    int *AB_r = (int *)malloc(size * sizeof(int));

    for (size_t i = 0; i < size; i++) {
        r[i] = rand() % 2;
    }

    mult_sq_matrix_vec(B, r, B_r);
    mult_sq_matrix_vec(C, r, C_r);
    mult_sq_matrix_vec(A, B_r, AB_r);

    for (size_t i = 0; i < size; i++) {
        if (AB_r[i] != C_r[i]) {

            free(r);
            free(B_r);
            free(C_r);
            free(AB_r);
            return false; 
        }
    }
    
    free(r);
    free(B_r);
    free(C_r);
    free(AB_r);
    return true; 
}