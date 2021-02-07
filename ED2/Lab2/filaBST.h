#include <stdio.h>
#include <stdlib.h>

typedef struct fila Fila;
typedef struct sentinel Sentinela;

Sentinela* criaFilaVazia();
void enqueue(void* data, Sentinela* queue);
void* dequeue(Sentinela* queue);
int isQueueEmpty(Sentinela*);
