#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadPag.h"

int filtra_Comando(char* comando){
  if(!strcmp(comando,"INSEREPAGINA")){
    return 0;
  }
  if(!strcmp(comando,"RETIRAPAGINA")){
    return 1;
  }
  if(!strcmp(comando,"INSEREEDITOR")){
    return 2;
  }
  if(!strcmp(comando,"RETIRAEDITOR")){
    return 3;
  }
  if(!strcmp(comando,"INSERECONTRIBUICAO")){
    return 4;
  }
  if(!strcmp(comando,"RETIRACONTRIBUICAO")){
    return 5;
  }
  if(!strcmp(comando,"INSERELINK")){
    return 6;
  }
  if(!strcmp(comando,"RETIRALINK")){
    return 7;
  }
  if(!strcmp(comando,"CAMINHO")){
    return 8;
  }
  if(!strcmp(comando,"IMPRIMEPAGINA")){
    return 9;
  }
  if(!strcmp(comando,"IMPRIMEWIKED")){
    return 10;
  }
  if(!strcmp(comando,"FIM")){
    return 11;
  }

  return -1;

}

int seleciona_Comando(FILE* arqEntrada){
  char comando[19];
  fscanf(arqEntrada," %s",comando);
  return filtra_Comando(comando);
}

void exec_Comandos(Lista* lista_pagina,Lista* editores,char* entrada){
  FILE* arqEntrada=fopen(entrada,"r"),*arqLog=fopen("log.txt","w");
  int filtro;
  char nome_Pag[20],editor[20],nome_Cont[20],nome_Arq[20],origem[20],destino[20];
  void* p;

  if(arqEntrada==NULL){
    printf("Erro de leitura do arquivo\n");
    exit(1);
  }

  //int cont=0;


  while(!feof(arqEntrada)){

    /*printf("FUNFANDO %d\n",cont);
    cont+=1;*/
    filtro=seleciona_Comando(arqEntrada);
    switch (filtro) {
      case 0: fscanf(arqEntrada," %s %s\n",nome_Pag,nome_Arq);
              INSERE_PAGINA(nome_Pag,nome_Arq,lista_pagina);
              break;

      case 1: fscanf(arqEntrada," %s\n",nome_Pag);
              RETIRA_PAGINA(lista_pagina,nome_Pag,arqLog);
              break;

      case 2: fscanf(arqEntrada," %s\n",editor);
              INSERE_EDITOR(editor,editores);
              break;

      case 3: fscanf(arqEntrada,"%s\n",editor);
              RETIRA_EDITOR(editor,editores, lista_pagina, arqLog);
              break;

      case 4: fscanf(arqEntrada," %s %s %s\n",nome_Pag,editor,nome_Cont);
              INSERE_CONTRIBUICAO(nome_Pag,editor,nome_Cont,lista_pagina,editores,arqLog);
              break;

      case 5: fscanf(arqEntrada," %s %s %s\n",nome_Pag,editor,nome_Cont);
              RETIRA_CONTRIBUICAO(nome_Pag,editor,nome_Cont,lista_pagina,arqLog);
              break;

      case 6: fscanf(arqEntrada," %s %s\n",origem,destino);
              INSERE_LINK(origem, destino, lista_pagina, arqLog);
              break;

      case 7: fscanf(arqEntrada," %s %s\n",origem,destino);
              RETIRA_LINK(origem,destino,lista_pagina,arqLog);
              break;

      case 8: fscanf(arqEntrada," %s %s\n",origem,destino);
              CAMINHO(origem,destino,lista_pagina,arqLog);
              break;

      case 9: fscanf(arqEntrada," %s\n",nome_Pag);
              p=(void*)busca_Pagina(lista_pagina,nome_Pag);
              if(p==NULL){
                fprintf(arqLog, "A PAGINA %s NAO EXISTE NA WIKIED!\n",nome_Pag);
              }
              IMPRIME_PAGINA(p);
              break;

      case 10: IMPRIME_WIKED(lista_pagina,arqLog);
               break;

      case 11: fclose(arqEntrada);
               fclose(arqLog);
               FIM(lista_pagina,editores);
               break;

      default: break;
    }
  }
}




int main(){
    Lista* paginas=cria_Lista(),* editores=cria_Lista();
    char entrada[100];
    scanf("%s",entrada);
    exec_Comandos(paginas,editores,entrada);
    return 0;
}
