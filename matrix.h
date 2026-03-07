#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

int** malloc_square_matrix(size_t size);
void free_square_matrix(int **matrix);
void rand_init_square_matrix(int **matrix, size_t range);

#endif 