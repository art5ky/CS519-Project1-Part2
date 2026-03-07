/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
*/

#ifndef LOCKS
#define LOCKS

void semaphore_init(int sem_id, int sem_num, int init_valve);
void semaphore_release(int sem_id, int sem_num);
void semaphore_reserve(int sem_id, int sem_num);

#endif