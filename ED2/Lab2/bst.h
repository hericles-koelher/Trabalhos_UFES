#include <stdlib.h>
#include <stdio.h>
#include "pilhaBST.h"
#include "filaBST.h"

typedef struct node Node;

Node* criaArvVazia();

Node* insereNo(int, Node*);

void liberaArv(Node*);

int altura(Node*);

void imprimirArvore(Node*);

void rec_preorder(Node *t, void (*p)(Node*));
void rec_inorder(Node *t, void (*p)(Node*));
void rec_postorder(Node *t, void (*p)(Node*));

void preorder_Pilha(Node *t, void (*p)(Node*));
void inorder_Pilha(Node *t, void (*p)(Node*));
void postorder_Pilha(Node *t, void (*p)(Node*));

void level_order(Node* t, void(*p)(Node*));
