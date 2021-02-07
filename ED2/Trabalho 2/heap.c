#include "heap.h"

static Item* bin;
static int in_use;

#define Giga 1000000

void init_Heap(int n){
    bin = malloc(sizeof(Item)*(n+1));
    in_use = 0;
}

Item create_bin(){
    Item x = Giga;

    return x;
}

static void top_Down_Heapify(int index){

    while(2*index <= in_use){
        int l = 2*index;

        if(l < in_use && bin[l] < bin[l+1]) l++;

        if(!less(bin[index],bin[l])) break;

        exch(bin[l],bin[index]);
        index = l;
    }
}

static void bottom_Up_Heapify(int index){

    while(index >= 2 && bin[index/2] < bin[index]){
        exch(bin[index/2],bin[index]);
        index /=2;
    }
}

void insert(Item x){
    in_use++;
    bin[in_use] = x;
    bottom_Up_Heapify(in_use);
}

Item del_MAX(){
    if(!in_use) return create_bin();

    exch(bin[1],bin[in_use]);
    in_use--;

    top_Down_Heapify(1);
    return bin[in_use+1];
}

Item use_Space(Item x, int length){
    return x -= length;
}

int disks_in_use(){
    return in_use;
}

void imprime(){
    for(int i = 1; i <= in_use; i++){
        printf("%d\n",bin[i]);
    }
}

void destroy_Heap(){
    free(bin);
}
