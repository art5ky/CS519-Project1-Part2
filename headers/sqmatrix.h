/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdbool.h>

int** malloc_sq_matrix(size_t size);
void free_sq_matrix(int **A);
void rand_init_sq_matrix(int **A);
void zero_init_sq_matrix(int **A);
void mult_sq_matrices_full(int **A, int **B, int **C);
void mult_sq_matrices_row(int row, int **A, int **B, int **C);
void mult_sq_matrix_vec(int **A, int *v, int *A_v);
void transpose_sq_matrix(int **A, int **A_T);
void mult_sq_matrices_row_transposed(int row, int **A, int **B, int **C);
void print_sq_matrix(int **A, const char *name);
bool same_matrix(int **A, int **B);
bool frievalds_verify(int **A, int **B, int **C, size_t size);
#endif 