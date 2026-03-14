/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
    Functions for handling matrix allocation and 
    multiplication logic. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <unistd.h>

// Locally create a matrix with contiguous memory allocation.
int** malloc_sq_matrix(size_t size) {
    size_t row_ptr_size = (size + 1) * sizeof(int*);
    size_t matrix_data_size = size * size * sizeof(int);

    int **rows = (int **)malloc(row_ptr_size);
    int *matrix_data = (int *)malloc(matrix_data_size);
    if (rows == NULL || matrix_data == NULL) {
        perror("couldn't allocate memory for matrix or row!");
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        rows[i] = &matrix_data[i * size];
    }
    // Sentinel value. Important for iterating through entries in matrix and knowing when to terminate loops. 
    rows[size] = NULL;
    return rows; 
}

// Similar to malloc_sq_matrix except matrices are not local and are sharable among processes.
int** malloc_sq_matrix_shared(size_t size) {
    size_t row_ptr_size = (size + 1) * sizeof(int*);
    size_t matrix_data_size = size * size * sizeof(int);

    int **rows = mmap(NULL, row_ptr_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *matrix_data = mmap(NULL, matrix_data_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (rows == MAP_FAILED || matrix_data == MAP_FAILED) {
        perror("couldn't allocate memory for matrix or row!");
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        rows[i] = &matrix_data[i * size];
    }
    // Sentinel value. Important for iterating through entries in matrix and knowing when to terminate loops. 
    rows[size] = NULL;
    return rows; 
}


void free_sq_matrix(int **A) {
    free(A[0]);
    free(A);
}

void free_sq_matrix_shared(int **A, size_t size) {
    munmap(A[0], size * size * sizeof(int));
    munmap(A, size * sizeof(int *));
}

// For matrix initalization, generate random integers in the entries. 
void rand_init_sq_matrix(int **A) {
    for (size_t i = 0; A[i] != NULL; i++) {
        for (size_t j = 0; A[j] != NULL; j++) {
            A[i][j] = rand();
        }
    }
}

void zero_init_sq_matrix(int **A) {
    for (size_t i = 0; A[i] != NULL; i++) {
        for (size_t j = 0; A[j] != NULL; j++) {
            A[i][j] = 0;
        }
    }
}

// Basic matrix multiplication function. Requires an initialized product matrix to store entries.
void mult_sq_matrices_full(int **A, int **B, int **C) {
    for (size_t i = 0; C[i] != NULL; i++) {
        for (size_t j = 0; C[j] != NULL; j++) {
            for (size_t k = 0; C[k] != NULL; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Similar to mult_sq_matrices, except we are passing the row index as a parameter for A. 
void mult_sq_matrices_row(int row, int **A, int **B, int **C) {
    for (size_t j = 0; C[j] != NULL; j++) {
        int sum = 0;
        for (size_t k = 0; C[k] != NULL; k++) {
            sum += A[row][k] * B[k][j];
        }
        C[row][j] = sum;
    }
}

void mult_sq_matrix_vec(int **A, int *v, int *A_v) {
    for (size_t j = 0; A[j] != NULL; j++) {
        int sum = 0;
        for (size_t k = 0; A[k] != NULL; k++) {
            sum += A[j][k] * v[k];
        }
        A_v[j] = sum;
    }
}

void transpose_sq_matrix(int **A, int **A_T) {
    for (size_t i = 0; A[i] != NULL; i++) {
        for (size_t j = 0; A[j] != NULL; j++) {
            A[j][i] = A_T[i][j];
        }
    }
}

// Similar to mult_sq_matrices_row, except this method of multiplication helps avoid CPU cache misses.
// Originally, incrementing row means jumping a large amount of bytes in memory to obtain the data.
void mult_sq_matrices_row_transposed(int row, int **A, int **B_T, int **C) {
    for (size_t j = 0; C[j] != NULL; j++) {
        int sum = 0;
        for (size_t k = 0; C[k] != NULL; k++) {
            sum += A[row][k] * B_T[j][k];
        }
        C[row][j] = sum;
    }
}

void print_sq_matrix(int **A, const char *name) {
    printf("\nMatrix %s entries:\n", name);
    for (size_t i = 0; A[i] != NULL; i++) {
        for (size_t j = 0; A[j] != NULL; j++) {
            printf("%3d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}