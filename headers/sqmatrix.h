/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdbool.h>

int** malloc_sq_matrix(size_t size);
void free_sq_matrix(int **matrix);
void rand_init_sq_matrix(int **matrix);
void zero_init_sq_matrix(int **matrix);
void mult_sq_matrices_full(int **pre_matrix, int **post_matrix, int **prod_matrix);
void mult_sq_matrices_row(int row, int **pre_matrix, int **post_matrix, int **prod_matrix);
void mult_sq_matrix_vec(int **matrix, int *post_vec, int *prod_vec);
void print_sq_matrix(int **matrix, const char *name);
bool same_matrix(int **pre_matrix, int **post_matrix);
bool frievalds_verify(int **A, int **B, int **C, size_t size);
#endif 