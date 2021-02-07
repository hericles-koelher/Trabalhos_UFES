#include "Sort.h"

void sort(Item *a, int lo, int hi){
    for(lo; lo < hi; lo++){
        for(int i = 0; i < hi - lo -1; i++){
            compexch(a[i],a[i+1]);
        }
    }
}
