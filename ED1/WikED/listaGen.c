#include "listaGen.h"

struct cel_Gen{
  void *info;
  struct cel_Gen* prox;
};

struct lista{
  cel_Gen* prim;
  cel_Gen* ult;
};

cel_Gen* cria_Cel_Gen(){
  cel_Gen* p=(cel_Gen*)malloc(sizeof(cel_Gen));

  p->info=NULL;
  p->prox=NULL;

  return p;
}

Lista* cria_Lista(){
  Lista* p=(Lista*)malloc(sizeof(Lista));

  p->prim=NULL;
  p->ult=NULL;

  return p;
}

void libera_lista(Lista* p){
  if(p==NULL){
    return;
  }
  cel_Gen* x=p->prim, *y;
  while(x!=NULL){
    y=x->prox;
    free(x);
    x=y;
  }
  free(p);
}

void insere(Lista* lista, void* dado){
  cel_Gen* m=cria_Cel_Gen();

  m->info=dado;

  if(lista_vazia(lista)){
    lista->prim=m;
    lista->ult=m;
    return;
  }

  lista->ult->prox=m;
  lista->ult=m;
}

int lista_vazia(Lista* lista){
  return lista->prim==NULL;
}

void andar_Lista(Lista *lista, void(*func)(void*)){
  cel_Gen* p=lista->prim;
  for(p;p!=NULL;p=p->prox){
    func(p->info);
  }
}

void* busca_Endereco(Lista *lista, void*(*func)(void*,void*), void* generico){
  if(lista_vazia(lista)){
    return NULL;
  }
  cel_Gen* p=lista->prim;
  void* r=NULL;
  for(p;p!=NULL;p=p->prox){
    r=func(p->info,generico);
    if(r!=NULL){
      return r;
    }
  }
  return NULL;
}

void* retira(Lista* lista, void* dado){
  cel_Gen* p=lista->prim,*ant;
  void* x;

  if(dado==NULL||p==NULL){
    return NULL;
  }

  if(dado==p->info){
    lista->prim=p->prox;
    x=p->info;
    free(p);
  }else{
    for(p;p!=NULL&&p->info!=dado;p=p->prox){
      ant=p;
    }
    ant->prox=p->prox;
    x=p->info;
    free(p);
  }
  return x;
}
