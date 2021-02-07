#include "item.h"

void sort(Item *a, int lo, int hi){
    for(int i = lo; i < hi/2; i++){

        for(int j = lo; j < hi - i - 1; j++){
            compexch(a[j],a[j+1]);
        }

        for(int k = hi-1; k >= hi/2 ;k--){
            compexch(a[k-1],a[k]);
        }
    }
}
