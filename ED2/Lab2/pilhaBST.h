#include <stdio.h>
#include <stdlib.h>

typedef struct pilha Pilha;
typedef struct gideon Gideon;

Gideon* criaPilhaVazia();
void push(void*, Gideon*);
void* pop(Gideon*);
int isPilhaVazia(Gideon*);
