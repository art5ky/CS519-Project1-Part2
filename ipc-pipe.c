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

#define MATRIX_SIZE 1000
#define ENTRY_RANGE 999

int main() {

    srand(time(NULL));
    struct timespec start, end; 
    long workers = sysconf(_SC_NPROCESSORS_ONLN);
    int base_rows = MATRIX_SIZE / workers; 
    int remainder = MATRIX_SIZE % workers; 

    printf("%d\n", base_rows);
    printf("%d\n", remainder);

    int **A = malloc_sq_matrix(MATRIX_SIZE);
    int **B = malloc_sq_matrix(MATRIX_SIZE);
    int **C = malloc_sq_matrix(MATRIX_SIZE);

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Allocation for matrices failed.");
        return 1; 
    }
    
    rand_init_sq_matrix(A, ENTRY_RANGE);
    rand_init_sq_matrix(B, ENTRY_RANGE);
    rand_init_sq_matrix(C, 1);

    clock_gettime(CLOCK_MONOTONIC, &start);
    mult_sq_matrices(A, B, C);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double total_time_sec = get_total_time(start, end);
   
    print_stats(MATRIX_SIZE, workers, true, total_time_sec);

    free_sq_matrix(A);
    free_sq_matrix(B);
    free_sq_matrix(C);
    return 0; 
}