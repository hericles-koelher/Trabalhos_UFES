#include "Sort.h"

void sort(Item *a, int lo, int hi){
    for(lo; lo < hi; lo++){
        for(int j = lo+1; j < hi; j++){
            compexch(a[lo],a[j]);
        }
    }
}
