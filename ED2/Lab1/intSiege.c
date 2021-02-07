#include "siege.h"

void* siege( void* n){

    int* vetor = calloc(*(int*)n-1,sizeof(int));

    for(int i = 0; i <= *(int*)n - 2; i++){
        for(int j = 0; j <= i/2; j++){
            if(!((i+2)%(j+2)) && i != 0){
                vetor[i] = 1;
            }
        }
    }

    return vetor;
}

void printSiege(void* vetor,void* n){

    for(int i = 0; i < *(int*)n - 2; i++){
        if(!((int*)vetor)[i]){
            printf("%d ",i+2);
        }
    }
    printf("\n");
}
