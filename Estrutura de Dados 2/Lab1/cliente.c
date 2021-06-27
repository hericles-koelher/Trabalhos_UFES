#include "siege.h"
#include <time.h>

int main(int argv, char** argc){
    int n = atoi(argc[1]);

    void* vetor = siege(&n);
    //printSiege(vetor,&n);
}
