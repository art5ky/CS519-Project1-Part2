/*  CS519, Spring 2026: Project 1 - Part 2
    Written by: Arthur Levitsky
    For implementing semaphores and ticket lock, man.archilinux.org reference was used.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdatomic.h>
#include <sys/mman.h>
#include <stddef.h>

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

typedef struct {
  atomic_uint ticket; 
  char ticket_padding[64];
  atomic_uint now_serving;
  char serving_padding[64];
} ticket_lock_t; 

ticket_lock_t* tl_create() {
  ticket_lock_t* lock = mmap(NULL, sizeof(ticket_lock_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (lock == MAP_FAILED) {
    perror("MMAP ticket lock memory page failed to create.");
    return NULL; 
  }
  atomic_init(&lock->ticket, 0);
  atomic_init(&lock->now_serving, 0);
  return lock; 
}

void tl_destroy(ticket_lock_t* lock) {
  if (lock) {
    munmap(lock, sizeof(ticket_lock_t));
  }
}

void tl_acquire(ticket_lock_t* lock) {
  unsigned int my_ticket = atomic_fetch_add(&lock->ticket, 1);
  while (atomic_load(&lock->now_serving) != my_ticket) {
    __builtin_ia32_pause();
  }
}

void tl_release(ticket_lock_t* lock) {
  atomic_fetch_add(&lock->now_serving, 1);
}

// Create one or more semaphores with read and write access.
int semaphore_create(int num_sems) {
  int sem_id = semget(IPC_PRIVATE, num_sems, 0666 | IPC_CREAT);
  if (sem_id == -1) {
    perror("Semaphore creation failed!");
    exit(EXIT_FAILURE);
  }
  return sem_id; 
}

// 
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