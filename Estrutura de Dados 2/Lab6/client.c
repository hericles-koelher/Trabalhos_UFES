#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "item.h"

extern void sort(Item *, int, int);

int main(int argc, char *argv[]) {
    // Input
    int N = atoi(argv[1]);

    Item *a = malloc(N * sizeof(Item));
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    // Sort
    clock_t start, stop;
    start = clock();
    sort(a, 0, N-1);
    stop = clock();

    // Output
    // for (int i = 0; i < N; i++) {
    //     printf("%d\n", a[i]);
    // }
    double time_taken = ((double) stop - start) / CLOCKS_PER_SEC;
    printf("\nElapsed time: %.3f\n", time_taken);

    free(a);
}
