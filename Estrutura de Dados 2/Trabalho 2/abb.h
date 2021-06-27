#ifndef ABB_H
#define ABB_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tree Tree;

/*inicia a abb*/
Tree* init_Tree();

/*insere um valor na abb*/
Tree* insert_Value(Tree*, int);

/*número de nós na abb*/
int nodes_In_Tree(Tree*);

/*liberação de memoria*/
void destroy(Tree*);

/*imprime nós da abb*/
void printOrder(Tree*);

/*search retorna (atráves do ponteiro para inteiro, sendo o valor inicial do inteiro definido obrigatoriamente
como -1 pelo usuario) a "chave" do nó que mais se aproxima da chave procurada, sendo a diferença de ambos >= 0*/
void search(Tree* t,int*, int);

/*remoção padrão de uma abb*/
Tree* remove_Tree(Tree*, int);

#endif
