/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
    Description: Basic single process matrix multiplication
    for upper-bounding time comparisons between IPC pipes and
    shared memory.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "headers/sqmatrix.h"
#include "headers/benchmark.h"

#define MATRIX_SIZE 1000

int main() {

    srand(time(NULL));
    struct timespec start, end; 

    int **A = malloc_sq_matrix(MATRIX_SIZE);
    int **B = malloc_sq_matrix(MATRIX_SIZE);
    int **C = malloc_sq_matrix(MATRIX_SIZE);

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Allocation for matrices failed.");
        return 1; 
    }
    
    rand_init_sq_matrix(A);
    rand_init_sq_matrix(B);
    zero_init_sq_matrix(C);

    clock_gettime(CLOCK_MONOTONIC, &start);
    mult_sq_matrices_full(A, B, C);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_time_sec = get_total_time(start, end);

    bool verified = verified_matrix(A, B, C, MATRIX_SIZE);

    //print_sq_matrix(A, "A");
    //print_sq_matrix(B, "B");
    //print_sq_matrix(C, "C");
   
    print_stats(MATRIX_SIZE, 1, verified, total_time_sec);

    free_sq_matrix(A);
    free_sq_matrix(B);
    free_sq_matrix(C);
    return 0; 
}