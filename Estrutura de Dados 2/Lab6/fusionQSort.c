#include <stdio.h>
#include <stdlib.h>
#include "item.h"

static int CUTOFF = 10;

Item median_of_3(Item* a, int lo, int hi){
    int mid = (lo+hi)/2;
    if(less(a[lo],a[mid]) && less(a[mid],a[hi])) return mid;
    else if(less(a[mid],a[lo]) && less(a[lo],a[hi])) return lo;
    else return hi;
}

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

int partition(Item* a, int lo, int hi) {
    int i = lo, j = hi+1;
    Item v = a[lo];
    while(1) {
        while(less(a[++i], v))// Find item on left to swap.
        if(i == hi)break;
        while
        (less(v, a[--j]))// Find item on right to swap.
        if(j == lo)break;
        if(i >= j)break;// Check if pointers cross.
        exch(a[i], a[j]);
    }
    exch(a[lo], a[j]);// Swap with partitioning item.
    return j;// Return index of item known to be in place.
}

void quick_sort(Item* a,int lo,int hi) {
    if(hi <= CUTOFF + lo -1){
        insert_sort(a,lo,hi);
        return;
    }

    int med = median_of_3(a,lo,hi);
    exch(a[lo],a[med]);
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j-1);
    quick_sort(a, j+1, hi);
}

void sort(Item* a,int lo,int hi) {
    //shuffle(a, hi-lo+1);// Needed for performance guarantee.
    quick_sort(a, lo, hi);
}
