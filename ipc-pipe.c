/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
    IPC using pipe to perform matrix multiplication.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "headers/sqmatrix.h"
#include "headers/benchmark.h"
#include "headers/locks.h"

#define SIZE 1000
#define RANGE 999

int main() {
    srand(time(NULL));
    struct timespec start, end; 
    
    int **A = malloc_sq_matrix(SIZE);
    int **B = malloc_sq_matrix(SIZE);
    int **C = malloc_sq_matrix(SIZE);

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Allocation for matrices failed.");
        return 1; 
    }
    
    rand_init_sq_matrix(A, RANGE);
    rand_init_sq_matrix(B, RANGE);
    rand_init_sq_matrix(C, 1);

    clock_gettime(CLOCK_MONOTONIC, &start);
    mult_sq_matrices(A, B, C);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_time_sec = get_total_time(start, end);
   
    print_stats(SIZE, 1, true, total_time_sec);

    free_sq_matrix(A);
    free_sq_matrix(B);
    free_sq_matrix(C);
    return 0; 
}