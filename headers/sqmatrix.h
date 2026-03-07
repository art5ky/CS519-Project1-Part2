#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

int** malloc_sq_matrix(size_t size);
void free_sq_matrix(int **matrix);
void rand_init_sq_matrix(int **matrix, size_t range);
void mult_sq_matrices(int **pre_matrix, int **post_matrix, int **prod_matrix);
void print_sq_matrix(int **matrix, const char *name);
#endif 