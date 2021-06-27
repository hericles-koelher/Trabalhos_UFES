#include <stdio.h>
#include <stdlib.h>
#include "item.h"
//Por mais incrivel que pareça essa versão rodou melhor que o mergeTopDown.c para 10000000 numeros aleatorios

#define SZ2 (sz+sz)
#define MIN(X,Y) ((X < Y) ? (X) : (Y))

void merge(Item* vet, Item* cp, int lo, int mid, int hi){
    for(int i = lo; i <= hi; i++) cp[i] = vet[i];

    int i = lo, j = mid+1;

    for(int k = lo; k <= hi; k++){
        if(i > mid) vet[k] = cp[j++];
        else if(j > hi) vet[k] = cp[i++];
        else if(less(cp[j],cp[i])) vet[k] = cp[j++];
        else vet[k] = cp[i++];
    }
}

void sort(Item *a, int lo, int hi) {
    int N = (hi - lo) + 1;
    int y = N - 1;
    Item *aux = malloc(N * sizeof(Item));
    for (int sz = 1; sz < N; sz = SZ2) {
        for (int lo = 0; lo < N-sz; lo += SZ2) {
            int x = lo + SZ2 - 1;
            merge(a, aux, lo, lo+sz-1, MIN(x,y));
        }
    }
    free(aux);
}
