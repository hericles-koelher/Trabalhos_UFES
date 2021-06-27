#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include <time.h>

extern void sort(Item *a, int lo, int hi);

int main(int argv, char** argc){
    Item *array, n = atoi(argc[1]);
    array = malloc(sizeof(array)*n);

    for(int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }
    clock_t ti  = clock();
    sort(array,0,n);
    printf("Time = %f\n",((clock() - ti / (double)CLOCKS_PER_SEC)));

    for(int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
    printf("\n");


}
