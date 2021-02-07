#include "filaBST.h"

struct fila{
    void* info;
    struct fila* next;
};

struct sentinel{
    Fila* head;
    Fila* tail;
};

Sentinela* criaFilaVazia(){
    Sentinela* x = malloc(sizeof(x));
    x->head = x->tail = NULL;
    return x;
}

void enqueue(void* data, Sentinela* queue){
    Fila* x = malloc(sizeof(x));
    x->info = data;
    x->next = NULL;

    if(queue->head == NULL){
        queue->head = queue->tail = x;
        //printf("Estava Vazia");
        return;
    }

    queue->tail->next = x;
    queue->tail = x;
}

void* dequeue(Sentinela* queue){
    if(queue->head == NULL){
        return NULL;
    }

    Fila* x = queue->head;
    queue->head = queue->head->next;

    return x->info;
}

int isQueueEmpty(Sentinela* x){
    return x->head == NULL;
}
