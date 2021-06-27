#include "siege.h"

void* siege(void* n){

    char* vetor = malloc(sizeof(char)*(*(int*)n-1));

    for(int i = 0; i <= *(int*)n - 2; i++){
        vetor[i] = 0;
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
