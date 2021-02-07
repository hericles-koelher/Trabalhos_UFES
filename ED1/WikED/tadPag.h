#ifndef __TADPAG_H
#define __TADPAG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaGen.h"
#include "tadContribuicao.h"

typedef struct pagina Pagina;

/*cria uma estrutura do tipo Pagina
* inputs:nenhum
* outputs: estrutura do tipo Pagina
* pré-condicao: nenhuma
* pós-condicao: estrutura criada e alocada*/
Pagina* cria_Pag(char *, char *);

/*insere uma nova pagina na lista de Paginas
* inputs: nome da pagina que será criada, nome do arquivo da pagina e a lista de Paginas
* outputs: nenhum
* pré-condicao: nenhuma
* pós-condicao: nova pagina criada e inserida na lista de paginas*/
void INSERE_PAGINA(char*, char*, Lista*);

/*exclui uma pagina da lista de Paginas
* inputs: a lista de paginas e nome da pagina que será retirada
* outputs: nenhum
* pré-condicao: a sentinela da lista existem
* pós-condicao: pagina retirada da lista de Paginas*/
void RETIRA_PAGINA(Lista *, char *,FILE*);

/*verifica se um dado que será convertido para tipo Pagina tem o mesmo nome que a string que será gerada pela conversão do segundo argumento
* inputs: 2 dados do tipo void, sendo o primeiro uma pagina convertida para void* e uma string convertida para void*
* outputs: endereco da pagina na memoria caso os nomes sejam iguais
* pré-condicao: o primeiro parametro é uma pagina convertida para void* e o segundo parametro é uma string convertida para void*
* pós-condicao: nenhuma */
void *nome_Igual_Pagina(void *, void *);

/*procura por uma pagina na lista de paginas e entrega seu endereço
* inputs: lista de paginas e o nome da pagina
* outputs: endereco da pagina procurada
* pré-condicao: sentinela da lista de paginas existe
* pós-condicao: nenhuma*/
Pagina *busca_Pagina(Lista * , char *);

/*retira uma contribuicao da lista de contribuições de uma pagina, mas mantendo ela no Historico
* inputs: nome da pagina, nome do editor, nome da contribuicao e lista de Paginas
* outputs: nenhum
* pré-condicao: nenhuma
* pós-condicao: contribuicao "retirada" mas ainda presente no historico*/
void RETIRA_CONTRIBUICAO(char *,char *,char * , Lista *,FILE*);

/*cria e insere um editor na lista de editores
* inputs: o nome do editor e a lista de editores
* outputs: nenhum
* pré-condicao: a string do nome de editor e a lista de editores existem
* pós-condicao: editor criado e colocado na lista de editores*/
void INSERE_EDITOR(char*,Lista*);

/*insere uma contribuicao na lista de contribuicoes de uma paginas
* inputs: strings contendo os nomes da pagina, editor e contribuição, além das listas de paginas e editores e o arquivo de logTXT
* outputs: neenhum
* pré-condicao: nenhuma das strings é nula e o editor já existe na lista de editores
* pós-condição: contribuição alocada e inserida na lista de contribuiçoes da pagina*/
void INSERE_CONTRIBUICAO(char *, char * , char *, Lista *, Lista *,FILE* );

/*insere um link entre duas Paginas
* inputs: strings de origem e destino, lista de paginas e arquivo de log
* outputs: nenhum
* pré-condição: strings, lista e arquivo não são nulos
* pós-condição: link do destino agora existe na lista de links da pagina da origem*/
void INSERE_LINK(char * , char *, Lista *, FILE*);

/*Retira o link de uma pagina destino em outra
* inputs: strings de origem e destino, lista de paginas e arquivo de log
* outputs: nenhum
* pré-condição: nenhuma
* pós-condição: link de destino não existe mais na pagina de origem*/
void RETIRA_LINK(char* , char*, Lista*, FILE*);

/*verifica se existe um caminho entre duas paginas
* inputs: strings com o nome da pagina origem e destino, lista de paginas e arquivo de log
* outputs: nenhum
* pré-condicao: strings, lista de paginas e arquivo de log existem
* pós-condicao: arquivo de log informa se existe ou não caminho entre as paginas*/
void CAMINHO(char* , char*, Lista*, FILE*);

/*Retira link da lista de uma pagina
* inputs: pagina q perdera o link, nome da pagina q terá link retirado
* outputs: pagina sem o links em questõa
* pré-condição: o link e a pagina em questão existem
* pós-condição: a pagina dada como parametro n possui o link em questão em sua lista*/
void* retira_link_da_lista(void* , void* );

/*escreve o nome de um link e o nome do arquivo desse link em um arquivo
* inputs: void pointer de Pagina e FILE
* outputs: nenhum
* pré-condicao: ambos os ponteiros não são nulos
* pós-condicao: nome do link e do arquivo do link escritos no arquivo dado como segundo parametro*/
void *escreve_links(void *, void *);

/*imprime uma pagina
* inputs: void pointer de uma Pagina
* outputs: nenhum
* pré-condicao: nenhuma
* pós-condicao: o arquivo da pagina foi criado e impresso*/
void IMPRIME_PAGINA(void *);

/* Imprime todas as paginas da WIKED! em arquivos
* inputs: lista de paginas e arquivo de log
* outputs: nenhum
* pré-condição: nenhum
* pós-condição: todas as paginas da WIKIED! foram impressas*/
void IMPRIME_WIKED(Lista *,FILE*);

/*libera toda a memoria usada pelo programa e encerra todas as atividades
* inputs: listas de pagina e editores
* outputs: nenhum
* pré-condição: lista de paginas e de editores não são nulas
* pós-condição: memoria liberada e execução do programa finalizada*/
void FIM(Lista*,Lista*);

/*retira um editor da lista de editores
* inputs: nome do editor que será retirado, lista de editores, lista de paginas e arquivo de log
* outputs: nenhum
* pré-condição: listas de pagina e endereco assim como arquivo de log existem
* pós-condição: editor e todas as suas contribuiçoes retirados*/
void RETIRA_EDITOR(char*, Lista*, Lista*,FILE*);

/* Atravez de recursão busca na estrutura dos links um caminho da origem ate o destino, sempre verificando se o link atual não esta voltando para algum que já foi checado.
* inputs: os void pointer da pagina que esta sendo checada e do link que ele deve procurar
* outputs: nome da pagina(caso seja encontado um caminho) ou NULL
* pré-condição: ambos os ponteiros dados como parametro existem
* pós-condição: nenhuma*/
void *procura_CAMINHO( void *, void *);

/* define que a pagina não foi visitada durante a checagem de CAMINHO
* inputs: void pointer de uma Pagina
* outputs: nenhum
* pré-condição: a pagina existe
* pós-condição: pagina pronta para uma nova checagem da função caminho */
void set_0(void*);

/* Libera a memoria alocada para uma pagina
* inputs: pagina que será liberada
* outputs: nenhum
* pré-condição: existencia da pagina
* pós-condição: pagina ja não existe e sua memoria foi liberada*/
void liberaPag(void*);

/* verifica se o editor de uma contribuicao é o mesmo que um editor qualquer apresentado
* inputs: void pointer de uma contribuicao e de um editor
* outputs: void contribuicao não é nula
* pré-condicao: ponteiro da contribuicao existe
* pós-condição:nenhuma*/
void* Editores_Iguais(void*, void*);

/*Retira as contribuicoes de um editor
* inputs: endereco da pagina a ser checada, endereco do editor
* outputs: nenhum
* pré-condição: nenhuma
* pós-condição: As contrubuições do editor foram tiradas*/
void* andar_Cont(void*, void*);

#endif
