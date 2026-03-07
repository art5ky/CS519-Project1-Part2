/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <sys/time.h>
#include <stdbool.h>

void print_stats(int matrix_size, int num_processes, int verified, double elapsed);
double get_total_time(struct timespec start, struct timespec end);

#endif