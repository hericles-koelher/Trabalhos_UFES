#include "Sort.h"

void sort(Item *a, int lo, int hi){
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
