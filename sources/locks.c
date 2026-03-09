/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
    For implementing semaphores, man.archilinux.org reference was used.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

int semaphore_create(int num_sems) {
  int sem_id = semget(IPC_PRIVATE, num_sems, 0666 | IPC_CREAT);
  if (sem_id == -1) {
    perror("Semaphore creation failed!");
    exit(EXIT_FAILURE);
  }
  return sem_id; 
}

void semaphore_destroy(int sem_id) {
  if (semctl(sem_id, 0, IPC_RMID) == -1) {
    perror("Semaphore removal failed!");
  }
}

void semaphore_init(int sem_id, int sem_num, int init_value) {
  union semun arg; 
  arg.val = init_value;

  if (semctl(sem_id, sem_num, SETVAL, arg) == -1) {
    perror("Semaphore initialization failed!");
    exit(EXIT_FAILURE);
  }
}

void semaphore_release(int sem_id, int sem_num) {
  struct sembuf sops; 
  sops.sem_num = sem_num; 
  sops.sem_op = 1; 
  sops.sem_flg = 0; 
  
  if (semop(sem_id, &sops, 1) == -1) {
    perror("Semaphore release failed!");
    exit(EXIT_FAILURE);
  }
}

void semaphore_reserve(int sem_id, int sem_num) {
  struct sembuf sops; 
  sops.sem_num = sem_num; 
  sops.sem_op = -1; 
  sops.sem_flg = 0; 

  if (semop(sem_id, &sops, 1) == -1) {
    perror("Semaphore reserve failed!");
    exit(EXIT_FAILURE);
  }
}