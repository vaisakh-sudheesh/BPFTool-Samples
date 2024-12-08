#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ALLOCS 1000000

int main() {
    printf("Allocation test!\n");

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < NUM_ALLOCS; i++) {
        int alloc_size = rand() % 1024;
        void *ptr = malloc(alloc_size); // Allocate 1KB
        if (ptr == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        free(ptr);
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d allocations: %f seconds\n", NUM_ALLOCS, cpu_time_used);

    return 0;
}