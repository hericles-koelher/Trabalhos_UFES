//
// Created by Bruno on 02/12/2020.
//

#include <stdio.h>
#include <pthread.h>
#include "Funcionarios.h"

void* corintianoWrapper(void* id){
    thread_corintiano((int*)id);
    return NULL;
}

void* palmeirenseWrapper(void* id){
    thread_palmeirense((int*)id);
    return NULL;
}

int main(){
    int id[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pthread_t tid[20] = {0};

    for(int i = 0; i < 10; i++){
        pthread_create(&tid[i], NULL, corintianoWrapper, &id[i]);
    }

    for(int i = 0; i < 10; i++){
        pthread_create(&tid[i + 10], NULL, palmeirenseWrapper, &id[i]);
    }

    for(int i = 0; i < 20; i++){
        pthread_join(tid[i], NULL);
    }

    return 0;
}