#include <stdlib.h>
#include <stdio.h>
#include <math.h>


# define SIZE 3

int main() {

    size_t A_len = SIZE * SIZE; 
    size_t total_bytes = A_len * sizeof(int);

    int *A = malloc(total_bytes);

    A[0] = 2;
    
    printf("%d\n", A[0]);
    printf("%zu", A_len);

    return 0; 
}