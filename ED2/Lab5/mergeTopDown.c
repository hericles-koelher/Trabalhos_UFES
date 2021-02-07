#include <stdio.h>
#include <stdlib.h>
#include "item.h"

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

void merge_Sort(Item* vet, Item* cp, int lo, int hi){
    if(hi <= lo) return;
    int mid = lo + (hi - lo)/2;
    merge_Sort(vet,cp,lo,mid);
    merge_Sort(vet,cp,mid+1,hi);
    merge(vet,cp,lo,mid,hi);
}

void sort(Item* vet, int lo, int hi){
    Item* cp = malloc(sizeof(Item)*hi);
    merge_Sort(vet,cp,lo,hi);
}
