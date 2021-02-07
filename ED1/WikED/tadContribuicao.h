#ifndef __TADCONTRIBUICAO_H
#define __TADCONTRIBUICAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaGen.h"


typedef struct contribuicao Contribuicao;
typedef struct editor Editor;

/*cria uma Contribuição
* inputs: strings com o nome da contribuicao, editor e a lista de editores
* outputs: estrutura de contribuicao criada e alocada
* pré-condicao: strings existem e lista de editores tambem
* pós-condicao: nenhuma*/
Contribuicao* cria_Contribuicao(char*, char*, Lista*, FILE*);

/*cria uma estrutura do tipo Editor*
* inputs: string com nome do editor
* outputs: estrutura de Editor com o nome do editor correspondente
* pré-condicao: a string com o nome do editor existem
* pós-condicao: estrutura criada e alocada*/
Editor* cria_editor(char *);

/*aloca memoria e copia a string para a nova string
* inputs: string contendo um nome
* outputs: endereco da string que foi alocada e possui o nome copiado
* pré-condicao: a string existe
* pós-condicao: nenhuma*/
char* copiaNome(char*);

/*compara uma string ao nome de editor presente na struct de editor informada como primeiro parametro
* inputs: string e estrutura de Editor retirada da lista generica
* outputs: endereco da estrutura que possui a nome igual a string informada
* pré-condicao:nenhuma
* pós-condicao:nenhuma*/
void* nome_Igual_Editor(void* ,void*);

/*procura um editor na lista de editores
* inputs: string com nome do editor,e lista de editores
* outputs: endereco da estrutura de editor que tem nome igual a string informada
* pré-condicao: sentinela da lista existe
* pós-condicao: nenhuma*/
Editor* busca_Editor(char* , Lista*);

/*libera a estrutura de editor
* inputs: a estrutura que será liberada
* outputs: nenhum
* pré-condicao: a estrutura de editor existe
* pós-condicao: a memoria alocada pela estrutura foi liberada*/
void free_editor(void*);

/*compara uma string ao nome da contribuicao presente na struct de Contribuicao informada como primeiro parametro
* inputs: string com nome do arquivo e Contribuicao retirada da lista generica
* outputs: endereco da estrutura de contribuicao caso seu nome seja igual ao da strings
* pré-condicao: nenhuma
* pós-condicao: nenhuma*/
void* nome_Igual_Contribuicao(void* ,void*);

/*entrega o endereco de uma contribuicao
* inputs: string com nome da contribuicao e a lista de Contribuicoes
* outputs: endereco da contribuicao
* pré-condicao: nenhuma
* pós-condicao: nenhuma*/
Contribuicao* busca_Contribuicao(Lista*, char*);

/*escreve o historico de contribuições com a formatação correta
* inputs: void pointer da contribuicao e do arquivo em que será escrito o Historico
* outputs: nenhum
* pré-condicao: a contribuicao e o arquivo existem
* pós-condicao: nome do editor e da contribuicao escritas no arquivo*/
void* escreve_historico_contribuicoes(void *, void *);

/*escreve o texto da contribuicao no arquivo escolhido
* inputs: void pointer da contribuicao e do arquivo em que o texto será escrito
* outputs: nenhum
* pré-condicao: a contribuicao e o arquivo existem
* pós-condicao: texto da contribuicao escrito no arquivo*/
void* escreve_contribuicao(void *, void *);

/*libera a memoria alocada para estrutura contribuicao
* inputs: a contribuicao que será liberada
* outputs: nenhum
* pré-condicao: a contribuicao que será liberada existem
* pós-condicao: a memoria da estrutura foi liberada*/
void free_Contribuicao(void*);

/*modifica o valor da variavel que "retira" a contribuição da lista de contribuicoes
* inputs: a contribuicao
* outputs: nenhum
* pré-condicao: a contribuicao existem
* pós-condicao: valor da variavel "retirado" da estrutura alterado para True*/
void esconde_Contribuicao(Contribuicao *);

/*verifica se o editor da contribuição analisada possui o mesmo nome que a string entregue como segundo parametro
* inputs: a estrutura de contribuicao e uma string com o nome do editor
* outputs: um numero diferente de 0 se a contribuicao foi criada pela pessoa cujo nome esta na string que é o segundo parametro ou 0 caso não seja
* pré-condicao: a estrutura de contribuicao existe e possui todos os campos preenchidos
* pós-condicao: nenhuma*/
int criou_Texto(Contribuicao* , char*);

/*verifica se uma estrutura do tipo Editor está presente em uma contribuicao
* inputs: estrutura do tipo Editor e estrutura do tipo Contribuicao
* outputs: 0 caso seja falso e != 0 caso contrario
* pré-condicao: ambas as estruturas informadas existem
* pós-condicao: nenhuma*/
int Ed_Igual(Editor*, Contribuicao*);


#endif
