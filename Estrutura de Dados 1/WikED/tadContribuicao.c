#include "tadContribuicao.h"
#define False 0;
#define True 1;

struct contribuicao{
  Editor *editor;
  char *nome;
  int retirado;
};

struct editor{
  char *nome;
};

char* copiaNome(char* nome){
    char* n=(char*)malloc((strlen(nome)+1)*sizeof(char));
    strcpy(n,nome);
    return n;
}

Editor* cria_editor(char *editor){
  Editor *p=(Editor*)malloc(sizeof(Editor));

  p->nome=copiaNome(editor);

  return p;
}

void* nome_Igual_Editor(void* editor,void*nome){
  if(editor==NULL){
    return NULL;
  }
  char* nome_Edi=(char*)nome;
  Editor* p=(Editor*)editor;

  if(!strcmp(p->nome,nome_Edi)){
    return p;
    }
  return NULL;
}


Editor* busca_Editor(char* editor, Lista* editores){
  void *nome_Edi=(void*)editor;

  Editor *p=(Editor*)busca_Endereco(editores,nome_Igual_Editor,nome_Edi);

  return p;
}


Contribuicao* cria_Contribuicao(char* nome, char* editor, Lista* editores, FILE* logTXT){
  Contribuicao *p=(Contribuicao*)malloc(sizeof(Contribuicao));
  Editor* ed=busca_Editor(editor,editores);

  if(ed==NULL){
    fprintf(logTXT, "O EDITOR %s NAO FOI CRIADO PREVIAMENTE\n",editor);
    return NULL;
  }

  p->editor=ed;
  p->nome=copiaNome(nome);
  p->retirado=False;

  return p;
}

void* nome_Igual_Contribuicao(void* contribuicao,void*nome){

  if(contribuicao==NULL){
    return NULL;
  }

  char* nome_Arq=(char*)nome;
  Contribuicao* p=(Contribuicao*)contribuicao;

  if(!strcmp(p->nome,nome_Arq)){
    return p;
    }

  return NULL;
}

Contribuicao* busca_Contribuicao(Lista* contribuicoes, char*nome){
  void* nome_Arq=(void*)nome;
  Contribuicao *p=(Contribuicao*)busca_Endereco(contribuicoes,nome_Igual_Contribuicao,nome_Arq);

  return p;
}

int criou_Texto(Contribuicao* p, char* edi){
  return (!strcmp(p->editor->nome,edi));
}

void esconde_Contribuicao(Contribuicao *p){
  p->retirado=True;
}


void free_Contribuicao(void* p){
  Contribuicao* x=(Contribuicao*)p;

  free(x->nome);
  free(x);

}

void *escreve_historico_contribuicoes(void *cont, void *arq){

  Contribuicao* contri=(Contribuicao*)cont;

  fprintf((FILE*)arq, "%s %s\n", contri->editor->nome, contri->nome);

  return NULL;
}

void *escreve_contribuicao(void *cont, void *arq){
  Contribuicao *contri = (Contribuicao *) cont;
  FILE *arquivo = (FILE*) arq;

  if(contri->retirado == 0){
    char caracter;

    FILE* arq_contribuicao = fopen(contri->nome, "r");

    if(arq_contribuicao==NULL){
      return NULL;
    }

    fprintf(arquivo, "\n-------- %s(%s) -------\n\n",contri->nome,contri->editor->nome );

    while( (caracter=fgetc(arq_contribuicao) )!= EOF ){

      fputc(caracter,arquivo);

    }

    fprintf(arquivo, "\n");

    fclose(arq_contribuicao);

  }

  return NULL;
}

void free_editor(void* editor){
  Editor* ed=(Editor*)editor;

  free(ed->nome);
  free(ed);

}

int Ed_Igual(Editor* ed, Contribuicao* cont){
  return ed==cont->editor;
}
