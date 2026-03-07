#include <sys/time.h>
#include <stdio.h>

void print_stats(int matrix_size, int num_processes, int verified, double elapsed) {
        printf("Input size: %d x %d\n",        matrix_size, matrix_size);
        printf("Number of processes: %d\n",    num_processes);
        printf("Verification: %s\n",           verified ? "PASS" : "FAIL");
        printf("Total runtime: %.6f seconds\n", elapsed);
    }

double get_total_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}
