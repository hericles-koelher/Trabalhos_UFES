#include "bst.h"

struct node{
    int info;
    struct node* left;
    struct node* right;
};

Node* criaArvVazia(){
    return NULL;
}

Node* insereNo(int info, Node* tree){
    if(tree == NULL){
        tree = malloc(sizeof(tree));
        tree->info = info;
        tree->left = tree->right = NULL;
        return tree;
    }else if(info < tree->info){
        tree->left = insereNo(info,tree->left);
    }else /*if(info > tree->info)*/{
        tree->right = insereNo(info,tree->right);
    }
    return tree;
}

void liberaArv(Node* x){
    liberaArv(x->left);
    liberaArv(x->right);
    free(x);
}

int maiorDeDois(int a, int b){
    return (a > b) ? a:b;
}

int altura(Node* tree){
    if(tree == NULL){
        return -1;
    }
    return 1 + maiorDeDois(altura(tree->left),altura(tree->right));
}

void imprimirArvore(Node* tree){
    printf("%d ", tree->info);
}

void rec_preorder(Node *t, void (*p)(Node*)){
    if(t == NULL){
        return;
    }
    p(t);
    rec_preorder(t->left,p);
    rec_preorder(t->right,p);
}

void rec_inorder(Node *t, void (*p)(Node*)){
     if(t == NULL){
         return;
     }
     rec_inorder(t->left,p);
     p(t);
     rec_inorder(t->right,p);

 }

void rec_postorder(Node *t, void (*p)(Node*)){
     if(t == NULL){
         return;
     }
     rec_postorder(t->left,p);
     rec_postorder(t->right,p);
     p(t);

 }

void preorder_Pilha(Node *t, void (*p)(Node*)){
     if(t == NULL){
         return;
     }

     Gideon* sentinel = criaPilhaVazia();

     push(t,sentinel);

     while (!isPilhaVazia(sentinel)) {
         Node* x = (Node*)pop(sentinel);

         p(x);

         if(x->right != NULL){
             push(x->right,sentinel);
         }

         if(x->left != NULL){
             push(x->left,sentinel);
         }
     }
 }

void inorder_Pilha(Node *t, void (*p)(Node*)){
      Gideon* sentinel = criaPilhaVazia();

      Node* raiz = t;

      while ((!isPilhaVazia(sentinel)) || raiz != NULL) {
          if(raiz != NULL){
              push(raiz,sentinel);
              raiz = raiz->left;
          }else{
              raiz = (Node*)pop(sentinel);
              p(raiz);
              raiz = raiz->right;
          }
      }
  }

void postorder_Pilha(Node *t, void (*p)(Node*)){
    Gideon* sentinel = criaPilhaVazia();

    Node* lastVisited = NULL, *y = t;

    while(!isPilhaVazia(sentinel) || y != NULL){
        if(y != NULL){
            push(y,sentinel);
            y = y->left;
        }else{
            Node* peek = (Node*)pop(sentinel);
            push(peek,sentinel);

            if(peek->right != NULL && peek->right != lastVisited){
                y = peek->right;
            }else{
                p(peek);
                lastVisited = (Node*)pop(sentinel);
            }
        }
    }
}

void level_order(Node* t, void(*p)(Node*)){
    if(t == NULL){
        return;
    }

    Sentinela* queue = criaFilaVazia();
    enqueue(t,queue);

    while(!isQueueEmpty(queue)){
        Node* x = (Node*)dequeue(queue);
        p(x);

        if(x->left != NULL){
            enqueue(x->left,queue);
        }
        if(x->right != NULL){
            enqueue(x->right,queue);
        }
    }
}
