#include "tadPag.h"
#define False 0;
#define True 1;

struct pagina{
  Lista *contribuicoes;
  Lista *links;

  char *nomePag;
  char *nomeArq;

  int check;
};


void INSERE_PAGINA(char* nomePag, char* nomeArq, Lista* lista_pagina){
  Pagina* p=cria_Pag(nomePag,nomeArq);

  insere(lista_pagina,p);
}

Pagina* cria_Pag(char *nome, char *nomeArq){
  Pagina *pag = (Pagina*)malloc(sizeof(Pagina));

  pag->contribuicoes = cria_Lista();

  pag->links = cria_Lista();

  pag->nomePag=copiaNome(nome);

  pag->nomeArq=copiaNome(nomeArq);

  pag->check=False;

  return pag;

}

void RETIRA_PAGINA(Lista *lista_pagina, char *nome, FILE* logTXT){
  void* nome_Pag=(void*)nome;
  Pagina *pag =(Pagina*) busca_Endereco(lista_pagina, nome_Igual_Pagina, nome_Pag);

  if(pag==NULL){
    fprintf(logTXT, "NAO EXISTE UMA PAGINA COM O NOME %s NA WIKIED!\n",nome);
    return;
  }

  busca_Endereco(lista_pagina,retira_link_da_lista,nome);

  andar_Lista(pag->contribuicoes,free_Contribuicao);
  libera_lista(pag->contribuicoes);

  libera_lista(pag->links);

  free(pag->nomeArq);
  free(pag->nomePag);

  free(pag);

}

void* retira_link_da_lista(void* pagina, void* lk){
  char* link=(char*)lk;
  Pagina* p=(Pagina*)pagina, *k=(Pagina*)busca_Pagina(p->links,link);
  Pagina* x=(Pagina*)retira(p->links,k);

  return x;
}

void *nome_Igual_Pagina(void *pag, void *nome){
  char* nome_Pag=(char*)nome;
  Pagina *saida = (Pagina*) pag;

  if(!strcmp(saida->nomePag, nome_Pag)){
    return saida;
  }

  return NULL;
}

Pagina *busca_Pagina(Lista* lista_pagina, char* nome){
  void* nome_Pag=(void*)nome;
  Pagina* p=(Pagina*)busca_Endereco(lista_pagina,nome_Igual_Pagina,nome_Pag);

  return p;
}

void INSERE_CONTRIBUICAO(char *pag, char* editor, char *contribuicao, Lista* lista_pagina, Lista* editores,FILE* logTXT){
  Pagina* pagina=busca_Pagina(lista_pagina,pag);

  if(pagina==NULL){
    fprintf(logTXT, "A PAGINA %s NAO EXISTE NA WIKIED!\n",pag);
    return;
  }

  Contribuicao* p=cria_Contribuicao(contribuicao,editor,editores,logTXT);

  if(p!=NULL)
    insere(pagina->contribuicoes,p);

}

void RETIRA_CONTRIBUICAO(char* Pag,char* editor,char* contribuicao, Lista* lista_pagina, FILE* logTXT){
  Pagina *pag=busca_Pagina(lista_pagina,Pag);
  if(pag==NULL){
    fprintf(logTXT, "A PAGINA %s DA CONTRIBUICAO %s NAO EXISTE\n",Pag,contribuicao);
    return;
  }

  Contribuicao* cont=busca_Contribuicao(pag->contribuicoes, contribuicao);
  if(cont==NULL){
    fprintf(logTXT, "CONTRIBUICAO %s NAO EXISTE\n",contribuicao);
    return;
  }

  if(criou_Texto(cont,editor)){
    esconde_Contribuicao(cont);
  }else{
    fprintf(logTXT, "O EDITOR %s NAO PODE RETIRAR O TEXTO %s\n",editor,contribuicao);
  }

}

void INSERE_LINK(char* origem, char* destino, Lista* lista_pagina,FILE* logTXT){
  Pagina *ori=busca_Pagina(lista_pagina,origem);

  if(ori==NULL){
    fprintf(logTXT, "A PAGINA DE ORIGEM %s NAO EXISTE NA WIKIED!\n",origem);
    return;
  }

  Pagina *des=busca_Pagina(lista_pagina,destino);

  if(des==NULL){
    fprintf(logTXT, "A PAGINA DE DESTINO %s NAO EXISTE NA WIKIED!\n",destino);
    return;
  }

  insere(ori->links,des);
}

void RETIRA_LINK(char* origem, char* destino, Lista* lista_pagina, FILE* logTXT){
  Pagina *ori=busca_Pagina(lista_pagina,origem);

  if(ori==NULL){
    fprintf(logTXT, "A PAGINA %s NAO EXISTE NA WIKIED!\n",origem);
  }

  Pagina *des=busca_Pagina(ori->links,destino);

  if(des==NULL){
    fprintf(logTXT, "NAO EXISTE UM LINK DE %s PARA %s\n",origem,destino);
  }

  retira(ori->links,des);

}

void *procura_CAMINHO( void *link1, void *nomePag1){
    Pagina *link = (Pagina*)link1;
    char *nomePag = (char*) nomePag1;

    if(link->check != 0){
        return NULL;
    }
    else if( !strcmp(link->nomePag,nomePag) ){
        return nomePag;
    }


    link->check = 1;

    busca_Endereco(link->links, procura_CAMINHO, nomePag1);

    return NULL;
}

void set_0(void* page){
  Pagina* pag=(Pagina*)page;
  pag->check=0;
}

void CAMINHO(char* origem, char* destino, Lista* lista_pagina, FILE* logTXT){
    Pagina *ori=busca_Pagina(lista_pagina,origem);

    if(ori==NULL){
        fprintf(logTXT, "A PAGINA %s NAO EXISTE, PORTANTO NAO HA CAMINHO ENTRE %s E %s\n",origem,origem,destino);
    }

    ori->check = 1;

    Pagina *des=busca_Pagina(ori->links,destino);

    if(des!=NULL){
        fprintf(logTXT, "HA CAMINHO DA PAGINA %s PARA %s\n",origem,destino);
        return;
    }
    else if( busca_Endereco(ori->links, procura_CAMINHO, (void*)destino) != NULL ){

            fprintf(logTXT, "HA CAMINHO DA PAGINA %s PARA %s\n",origem,destino);
    }else{
        fprintf(logTXT, "NAO HA CAMINHO DA PAGINA %s PARA %s\n",origem,destino);
    }

    andar_Lista(lista_pagina,set_0);

    return;
}

void IMPRIME_PAGINA(void* pagina){
  Pagina* p=(Pagina*)pagina;

  if(p!=NULL){
      FILE* arquivo=fopen(p->nomeArq,"w");

      //Nome da pagina
      fprintf(arquivo, "%s\n\n",p->nomePag);

      //lista de historico de contribuicao
      fprintf(arquivo, "--> Historico de Contribuicoes\n");
      busca_Endereco(p->contribuicoes, escreve_historico_contribuicoes, arquivo);
      fprintf(arquivo, "\n");

      //lista de links na PAGINA
      fprintf(arquivo, "--> Links\n");
      busca_Endereco(p->links, escreve_links, arquivo);
      fprintf(arquivo, "\n");

      //Textos das contribuicoes/
      fprintf(arquivo, "--> Textos\n");
      busca_Endereco(p->contribuicoes, escreve_contribuicao, arquivo);
      //fprintf(arquivo, "\n\n");

      fclose(arquivo);

  }

}


void IMPRIME_WIKED(Lista *lista_pagina,FILE* logTXT){
  if(lista_pagina==NULL){
    fprintf(logTXT, "A WIKED! AINDA NAO EXISTE\n");
    return;
  }

  andar_Lista(lista_pagina,IMPRIME_PAGINA);
}

void *escreve_links(void *l, void  *arq ){
  Pagina *link = (Pagina*)l;

  fprintf((FILE*)arq, "%s %s\n", link->nomePag, link->nomeArq);

  return NULL;
}

void liberaPag(void* pag){
  Pagina* Page=(Pagina*)pag;

  andar_Lista(Page->contribuicoes,free_Contribuicao);
  libera_lista(Page->contribuicoes);
  libera_lista(Page->links);


  free(Page->nomePag);
  free(Page->nomeArq);
  free(Page);
}

void FIM(Lista* lista_pagina,Lista* editores){
  andar_Lista(lista_pagina,liberaPag);
  libera_lista(lista_pagina);

  andar_Lista(editores,free_editor);
  libera_lista(editores);

  exit(1);
}

void* Editores_Iguais(void* cont, void* ed){
  Contribuicao* contr=(Contribuicao*)cont;
  Editor* ed1=(Editor*)ed;

  if(Ed_Igual(ed1,contr))
    return cont;

  return NULL;
}

void* andar_Cont(void* pag, void* ed){
  Pagina* page=(Pagina*)pag;
  void* x=busca_Endereco(page->contribuicoes,Editores_Iguais,ed);
  Contribuicao* y;

  while(x!=NULL){
    y=(Contribuicao*)retira(page->contribuicoes,x);
    free_Contribuicao(y);
    x=busca_Endereco(page->contribuicoes,Editores_Iguais,ed);
  }

  return NULL;

}

void RETIRA_EDITOR(char* editor, Lista* editores, Lista* lista_pagina,FILE* logTXT){
  Editor* ed=busca_Editor(editor,editores);

  if(ed==NULL){
    fprintf(logTXT, "O EDITOR %s NAO FOI INSERIDO AINDA\n",editor);
    return;
  }

  busca_Endereco(lista_pagina,andar_Cont,ed);

  free_editor(retira(editores,ed));

}

void INSERE_EDITOR(char* editor,Lista* editores){
  Editor *p=cria_editor(editor);

  insere(editores,p);
}
