#include <stdio.h>
#include <stdlib.h>
#include "item.h"
//Incompleto
#define CUTOFF 8
#define SZ2 (sz+sz)
#define MIN(X,Y) ((X < Y) ? (X) : (Y))

void insert_sort(Item *a, int lo, int hi){
    Item c;
    for(int i = lo; i < hi; i++){
        for(int j = lo; j < i; j++){
            if(less(a[i],a[j])){
                c = a[i];
                for(int k = i; k >= j; k--){
                    a[k] = a[k-1];
                }
                a[j] = c;
                continue;
            }
        }
    }
}

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

    int sz = CUTOFF;
    for (int low = lo; low < N; low += sz) {
        int x = low + sz - 1;
        insert_sort(a, low, MIN(x,y));
    }

    Item *aux = malloc(N * sizeof(Item));
    for (int sz = CUTOFF; sz < N; sz = SZ2) {
        for (int lo = 0; lo < N-sz; lo += SZ2) {
            int x = lo + SZ2 - 1;
            merge(a, aux, lo, lo+sz-1, MIN(x,y));
        }
    }
    free(aux);
}
