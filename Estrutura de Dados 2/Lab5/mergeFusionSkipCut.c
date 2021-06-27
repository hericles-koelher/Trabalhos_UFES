#include <stdio.h>
#include <stdlib.h>
#include "item.h"

static int CUTOFF = 8;

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

void merge_sort(Item *a, Item *aux, int lo, int hi) {
    if (hi <= lo + CUTOFF - 1) {
        insert_sort(a, lo, hi);
        return;
    }
    int mid = lo + (hi - lo) / 2;
    merge_sort(a, aux, lo, mid);
    merge_sort(a, aux, mid+1, hi);
    if (!less(a[mid+1], a[mid])) return;
    merge(a, aux, lo, mid, hi);
}

void sort(Item* vet, int lo, int hi){
    Item* cp = malloc(sizeof(Item)*hi);
    merge_sort(vet,cp,lo,hi);
}
