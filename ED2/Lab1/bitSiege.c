#include "siege.h"

#define Byte unsigned char
#define conv(a,b) (a * 8) + b + 2

void* siege(void* n){
    Byte* vetor = malloc(sizeof(Byte)*(*(int*)n/8+1));
    int b;

    for(int i = 0; i < *(int*)n/8+1; i++){

        vetor[i] = 0;

        for(int k = 0; k < 8; k++){

            b = conv(i,k);
            if(b == *(int*)n){
                return vetor;
            }

            for(int x = 2; x <= b/2; x++){
                 
                if(!(b % x) && b != 2){
                    vetor[i] = vetor[i] | 0x01 << (7 - k);
                    continue;
                }
            }
        }
    }

    return vetor;
}

void printSiege(void* vetor,void* n){
    Byte* x = (Byte*)vetor;
    int b;

    for(int i = 0; i < *(int*)n/8+1; i++){
        for(int j = 0; j < 8; j++){
            b = conv(i,j);

            if(b == *(int*)n){
                printf("\n");
                return;
            }

            if(!(x[i] >> (7-j) & 0x01)){
                printf("%d ",b);
            }
        }
    }
    printf("\n");
}
