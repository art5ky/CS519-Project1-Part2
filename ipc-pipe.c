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
#define ENTRY_RANGE 100

int main() {

    srand(time(NULL));
    struct timespec start, end; 

    // Create num_workers processes based on number of logical cores in the system.
    long num_workers = sysconf(_SC_NPROCESSORS_ONLN);
    int base_rows = MATRIX_SIZE / num_workers; 
    int remainder = MATRIX_SIZE % num_workers; 

    int **A = malloc_sq_matrix(MATRIX_SIZE);
    int **B = malloc_sq_matrix(MATRIX_SIZE);
    int **C = malloc_sq_matrix(MATRIX_SIZE);

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Allocation for matrices failed.");
        return 1; 
    }
    
    // ENTRY_RANGE dictates entries with values between 0 to ENTRY_RANGE.
    rand_init_sq_matrix(A, ENTRY_RANGE);
    rand_init_sq_matrix(B, ENTRY_RANGE);
    
    // Initialize matrix C with value 0.
    rand_init_sq_matrix(C, 1);

    //print_sq_matrix(A, "A");
    //print_sq_matrix(B, "B");

    // Creating the shared pipe among child processes.
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed!");
        return 1; 
    }

    // Create 1 semaphore and initalize unlock to value 1.
    int sem_id = semaphore_create(1);
    semaphore_init(sem_id, 0, 1);

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < num_workers; i++) {
        pid_t pid = fork(); 

        if (pid == -1) {
            perror("Failed creating child process!");
            return 1; 
        }

        // Child process successfully created. Begin work...
        if (pid == 0) {
            close(pipefd[0]);

            // Based on the subdivisions per child process, calculate the starting and ending rows factoring in remainders.
            int start_row = i * base_rows + (i < remainder ? i : remainder);
            int end_row = start_row + base_rows + (i < remainder ? 1 : 0);

            for (int r = start_row; r < end_row; r++) {
                mult_sq_matrices_by_row(r, A, B, C);

                // Child reserves the lock and writes to the pipe buffer. It includes the row number and column of integers computed.
                semaphore_reserve(sem_id, 0);

                write(pipefd[1], &r, sizeof(int));
                write(pipefd[1], C[r], MATRIX_SIZE * sizeof(int));

                semaphore_release(sem_id, 0);
            }

            // Once child has computed all of its designated rows, close the writing file descriptor and exit successfully.
            close(pipefd[1]);
            exit(0); 
        }
    }

    close(pipefd[1]);

    // Read the data from the pipe on the parent process and add the computed data onto parent's matrix C.
    int target_row; 
    while (read(pipefd[0], &target_row, sizeof(int)) > 0) {
        read(pipefd[0], C[target_row], MATRIX_SIZE * sizeof(int));
    }

    close(pipefd[0]);

    // Wait for all child processes to terminate. If something goes wrong in termination, report errors.
    for (int i = 0; i < num_workers; i++) {
        int status; 
        pid_t child_pid = wait(&status);

        if (!WIFEXITED(status)) {
            fprintf(stderr, "Child process: %d terminated abnormally!\n", child_pid);
        } else {
            int exit_code = WEXITSTATUS(status);
            if (exit_code != 0) {
                fprintf(stderr, "Child process: %d failed with code: %d\n", child_pid, exit_code);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double total_time_sec = get_total_time(start, end);

    //print_sq_matrix(C, "C");

    // Verify the matrix with sequential matrix multiplication up to 1000 MATRIX_SIZE.
    // If larger than 1000 MATRIX_SIZE, then use Freivald's algorithm for matrix correctness.
    bool verified;
    if (MATRIX_SIZE <= 1000) {

        int **D = malloc_sq_matrix(MATRIX_SIZE);
        rand_init_sq_matrix(D, 1);

        if (D == NULL) {
            fprintf(stderr, "Allocation for matrix D failed.");
            return 1;
        }
        mult_sq_matrices(A, B, D);
        verified = same_matrix(C, D);
    } else {
        // CREATE FRIEVALDS LOGIC HERE ----------------------
        verified = false;
    }
   
    print_stats(MATRIX_SIZE, num_workers, verified, total_time_sec);

    semaphore_destroy(sem_id);
    free_sq_matrix(A);
    free_sq_matrix(B);
    free_sq_matrix(C);
    return 0; 
}