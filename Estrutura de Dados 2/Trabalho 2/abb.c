#include "abb.h"

struct tree{
  int space;
  struct tree *left, *right;
};

#define Giga 1000000
#define exch(A,B) {Tree* t = A; A = B; B = t;}

static int fit(Tree* t, int k) {return (t->space - k) >= 0;}

Tree* init_Tree(){
    return NULL;
}

static Tree* create_Tree(int space, Tree* l, Tree* r){
    Tree *x = malloc(sizeof(Tree));
    x->space = space;
    x->left = l;
    x->right = r;
    return x;
}

Tree* insert_Value(Tree* t, int space){
    if(t == NULL){
      return create_Tree(space,init_Tree(),init_Tree());
    }

    if(space < t->space){
      t->left = insert_Value(t->left,space);
    }else{
      t->right = insert_Value(t->right,space);
    }
    return t;
}

void search(Tree* t,int* aux, int space){

    if(t == NULL) return;

    if(fit(t,space)){
        if(*aux == -1) *aux = t->space;
        else{
            if((*aux - space) > (t->space - space)) *aux = t->space;
        }
        search(t->left,aux,space);
    }else{
        search(t->right, aux, space);
    }
}

Tree* remove_Tree(Tree* t, int k){
    if(t == NULL) return NULL;

    if(k < t->space) t->left = remove_Tree(t->left,k);

    else if(k > t->space) t->right = remove_Tree(t->right,k);

    else if(t->left == NULL && t->right == NULL) {
      free(t);
      t = NULL;
    }
    else if(t->right == NULL){
        Tree* aux = t;
        t = t->left;
        free(aux);
    }else if(t->left == NULL){
        Tree* aux = t;
        t = t->right;
        free(aux);
    }else{
        Tree* aux = t->left;

        while(aux->right != NULL){
            aux = aux->right;
        }

        int auxT = t->space;
        t->space = aux->space;
        aux->space = auxT;

        t->left = remove_Tree(t->left,k);
    }
    return t;
}

void printOrder(Tree *t){
    if(t){
      printOrder(t->left);
      printf("%d - ", t->space);
      printOrder(t->right);
    }
}

int nodes_In_Tree(Tree* t){
    if(t){
        return 1 + nodes_In_Tree(t->left) + nodes_In_Tree(t->right);
    }
    return 0;
}

void destroy(Tree* t){
    if(t){
      destroy(t->left);
      destroy(t->right);
      free(t);
    }
}
