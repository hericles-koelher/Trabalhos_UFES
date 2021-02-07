#include "arvore.h"

struct arv{
    unsigned char info;
    int cont;
    struct arv* esq;
    struct arv* dir;
};

Arv* arv_criavazia (void){
  return NULL;
}

Arv* arv_cria (unsigned char c,int x, Arv* e, Arv* d){
  Arv* p=(Arv*)malloc(sizeof(Arv*));

  p->info=c;
  p->cont=x;
  p->esq=e;
  p->dir=d;

  return p;
}

Arv* arv_libera (Arv* a){

  if(!arv_vazia(a)){
    arv_libera(a->esq);
    arv_libera(a->dir);
    free(a);
  }

  return NULL;
}

int arv_vazia (Arv* a){
  return a == NULL;
}

void arv_imprime (Arv* a){
  printf(" <");
  if(!arv_vazia(a)){
    printf("%c ",a->info);
    arv_imprime(a->esq);
    arv_imprime(a->dir);
  }
  printf("> ");
}

unsigned char info (Arv* a){
  return a->info;
}

int arv_Pertence_Folha (Arv* a, unsigned char c){
  if(!arv_vazia(a)){
      return (a->info == c && ehFolha(a)) || arv_Pertence_Folha(a->esq,c) || arv_Pertence_Folha(a->dir,c);
    }

  return 0;
}

int numero_Frequencia(Arv* x){
  return x->cont;
}

void gera_Codigo_Char(Arv* x, unsigned char c, char* codigo, int tam){

    if(arv_Pertence_Folha(x->esq,c)){
            codigo[tam]='0';
            gera_Codigo_Char(x->esq,c,codigo,tam+1);
        }
    else if(arv_Pertence_Folha(x->dir,c)){
            codigo[tam]='1';
            gera_Codigo_Char(x->dir,c,codigo,tam+1);
    }
    else{
            codigo[tam]='\0';
    }
}

Arv* caminhar(Arv* x, int n){
    if(n == 1){
        return x->dir;
    }else if(n == 0){
        return x->esq;
    }
    return NULL;
}

static int maior(int a, int b){
    return (a > b)? a:b;
}

int altura(Arv* x){
    if(arv_vazia(x)){
        return -1;
    }
    return 1+maior(altura(x->esq),altura(x->dir));
}

int ehFolha(Arv *x){
    return (arv_vazia(x->esq) && arv_vazia(x->dir));
}
