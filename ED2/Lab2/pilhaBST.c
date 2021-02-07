#include "pilhaBST.h"

struct pilha{
    void* info;
    struct pilha* prox;
};

struct gideon{
    Pilha* topo;
};

Gideon* criaPilhaVazia(){
    Gideon* x = malloc(sizeof(x));
    x->topo = NULL;
    return x;
}

void push(void* x, Gideon* y){
    Pilha* m = malloc(sizeof(m));

    m->info = x;
    m->prox = y->topo;

    y->topo = m;
}

void* pop(Gideon* y){
    if(isPilhaVazia(y)){
        return NULL;
    }
    void* x = y->topo->info;
    y->topo = y->topo->prox;

    return x;
}

int isPilhaVazia(Gideon* x){
    return x->topo == NULL;
}
