#include "bin_packing_solution.h"

#define Giga 1000000

int worst_fit(int* numbers, int n){
    init_Heap(n);

    for(int i = 0; i < n; i++){
        Item aux = del_MAX();

        if(less(aux,numbers[i])){
            insert(aux);
            aux = create_bin();
        }
        aux = use_Space(aux,numbers[i]);
        insert(aux);

    }
    int result = disks_in_use();
    destroy_Heap();
    return result;
}

/*remove_Best procura "melhor nó" e o remove da lista
o valor de memoria do disco retirado é entregue ao best fit por meio do ponteiro pra inteiro auxI.
Esse "melhor nó" é definido pela função search como sendo o nó que possui valor mais proximo ao de space,
desde que seja maior ou igual que 0 a diferença de ambos*/
static Tree* remove_Best(Tree* t, int space, int* auxI){
    *auxI = -1;

    search(t,auxI,space);

    if(*auxI == -1) {
        *auxI = Giga;
        return t;
    }

    return remove_Tree(t,*auxI);
}

int best_fit(int* numbers, int n){
    Tree* t = init_Tree();

    for(int i = 0; i < n; i++){
        int bin;
        t = remove_Best(t,numbers[i],&bin);
        bin -= numbers[i];
        t = insert_Value(t,bin);
    }

    int result = nodes_In_Tree(t);

    destroy(t);

    return result;
}
