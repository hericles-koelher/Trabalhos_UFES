#ifndef __LISTAGEN_H
#define __LISTAGEN_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cel_Gen cel_Gen;
typedef struct lista Lista;


/*cria uma celula da lista generica
*inputs: nenhum
* outputs: celula criada
* pré-condicao: nenhuma
* pós-condicao: celula criada e alocada*/
cel_Gen* cria_Cel_Gen();

/*cria a sentinela da lista generica
* inputs: nenhum
* outputs: sentinela da lista
* pré-condicao: nenhuma
* pós-condicao: sentinela criada e alocada*/
Lista* cria_Lista();

/*libera todas as posições da lista generica (exceto o dado armazenad)
* inputs:sentinela da lista
* outputs: nenhum
* pré-condicao: nenhuma
* pós-condicao: memoria da lista liberada*/
void libera_lista(Lista*);

/*insere um dado na lista
* inputs: sentinela da lista e o elemento que seŕa inserido
* outputs: nenhum
* pré-condicao: sentinela da lista existe
* pós-condicao: informação inserida na lista*/
void insere(Lista*, void*);

/*verifica se a lista é vazia
* inputs:sentinela da lista
* outputs: 1 se a lista for vazia e 0 caso não seja
* pré-condicao: lista existe
* pós-condicao: nenhuma*/
int lista_vazia(Lista*);

/*percorre a lista
* inputs: sentinela da lista e nome da função callback que será utiliazada
* outputs:nenhum
* pré-condicao: a lista e a função callback existem
* pós-condicao: nenhuma*/
void andar_Lista(Lista*, void(*)(void*));

/*percorre a lista e retorna um endereco
* inputs: sentinela da lista, função callback que será utiliazada e uma string
* outputs: endereco retornado pela funçao callback
* pré-condicao: sentinela da lista e função callback existem
* pós-condicao: nenhuma*/
void* busca_Endereco(Lista*, void*(*)(void*,void*), void*);

/*retira um elemento da lista e libera a celula da lista que carregava o elemento
* inputs:sentinela da lista e dado que sera retirado
* outputs: dado que foi retirado da lista
* pré-condicao: sentinela da lista existe
* pós-condicao: dado retirado da lista e a lista continua consistente*/
void* retira(Lista*, void*);

/*inputs: sentinela da lista
* outputs: numero de celulas da lista
* pré-condicao: sentinela da lista existe
* pós-condicao: nenhuma*/
int tam_Lista(Lista*);

/*inputs: sentinela da lista e um número  inteiro corresponde a "posição" de uma celula na lista
* outputs: celula da "posição" solicitada
* pré-condicao: sentinela da lista existe e o numero é maior ou igual a 0 e menor que o tamanho da lista
* pós-condicao: nenhuma */
cel_Gen* return_Cel(Lista*, int);

/*inputs: sentinela da lista
* outputs: informação da primeira celula da lista
* pré-condicao: sentinela da lista existe
* pós-condicao: primeira celula da lista retirada*/
void* retira_Topo(Lista*);

/*inputs: sentinela da lista, dado que será inserido, e função callback que será executada na lista
* outputs: nenhum
* pré-condicao: sentinela da lista e função callback existem
* pós-condicao: elemento inserido na lista de maneira ordenada*/
void insertion_Sort(Lista *, void*, int (cb)(void*,void*));

#endif
