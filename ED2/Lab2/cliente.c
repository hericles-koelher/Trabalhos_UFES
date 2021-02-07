#include "bst.h"
#include <time.h>

int main(){

    printf("Insira o número de chaves que serão geradas\n");

    int n;
    double rPR, rIN, rPO, piPR, piIN, piPO;
    scanf("%d",&n);

    Node* arvore = criaArvVazia();

    srand(time(NULL));

    for(int i = 0; i < n; i++){
        arvore = insereNo(rand()%100,arvore);
    }

    clock_t ti = clock();
    rec_preorder(arvore,imprimirArvore);
    rPR = (clock() - ti) / (double)CLOCKS_PER_SEC;
    printf("\n");

    ti = clock();
    rec_inorder(arvore,imprimirArvore);
    rIN = (clock() - ti) / (double)CLOCKS_PER_SEC;
    printf("\n");

    ti = clock();
    rec_postorder(arvore,imprimirArvore);
    rPO = (clock() - ti) / (double)CLOCKS_PER_SEC;
    printf("\n");

    ti = clock();
    preorder_Pilha(arvore,imprimirArvore);
    piPR = (clock() - ti) / (double)CLOCKS_PER_SEC;
    printf("\n");

    ti = clock();
    inorder_Pilha(arvore,imprimirArvore);
    piIN = (clock() - ti) / (double)CLOCKS_PER_SEC;
    printf("\n");

    ti = clock();
    postorder_Pilha(arvore,imprimirArvore);
    piPO = (clock() - ti) / (double)CLOCKS_PER_SEC;
    printf("\n");

    //printf("Altura %d\n",altura(arvore));


    printf("Comparação versões Recursivas x Iterativas\nPre-Order: %f - %f\nIn-Order: %f - %f\nPost-Order: %f - %f\n",rPR,piPR,rIN,piIN,rPO,piPO);

    printf("Level Order\n");

    level_order(arvore,imprimirArvore);
    printf("\n");
}
