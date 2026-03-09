/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdbool.h>

int** malloc_sq_matrix(size_t size);
void free_sq_matrix(int **matrix);
void rand_init_sq_matrix(int **matrix, size_t range);
void mult_sq_matrices(int **pre_matrix, int **post_matrix, int **prod_matrix);
void mult_sq_matrices_by_row(int row, int **pre_matrix, int **post_matrix, int **prod_matrix);
void print_sq_matrix(int **matrix, const char *name);
bool same_matrix(int **pre_matrix, int **post_matrix);

#endif 