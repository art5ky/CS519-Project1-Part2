/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include "../headers/sqmatrix.h"

void print_stats(int matrix_size, int num_processes, bool verified, double elapsed) {
        printf("Input size: %d x %d\n",        matrix_size, matrix_size);
        printf("Number of processes: %d\n",    num_processes);
        printf("Verification: %s\n",           verified ? "PASS" : "FAIL");
        printf("Total runtime: %.6f seconds\n", elapsed);
    }

double get_total_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

bool verified_matrix(int **A, int **B, int **C, size_t size) {
    if (size <= 1000) {
        int **prod_matrix = malloc_sq_matrix(size);
        zero_init_sq_matrix(prod_matrix);

        if (prod_matrix == NULL) {
            fprintf(stderr, "Allocation for matrix D failed!");
            return false; 
        }
        mult_sq_matrices_full(A, B, prod_matrix);
        bool verified = same_matrix(C, prod_matrix);
        free_sq_matrix(prod_matrix);
        return verified;
    } else {
        return frievalds_verify(A, B, C, size);
    }
}