#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include "item.h"

/*inicia a heap estatica com tamanho definido*/
void init_Heap(int);

/*cria e retorna um novo item da heap*/
Item create_bin();

/*insere um item na heap*/
void insert(Item);

/*deleta o maior valor da heap*/
Item del_MAX();

/*altera o valor do item "usando" o espaço disponivel*/
Item use_Space(Item, int);

/*retorna a quantidade de elementos presentes na heap de discos*/
int disks_in_use();

/*libera memoria*/
void destroy_Heap();

#endif
