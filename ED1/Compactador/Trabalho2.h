#ifndef __TRABALHO2_H
#define __TRABALHO2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "listaGen.h"
#include "arvore.h"
#include "bitmap.h"

//COMPACTADOR
/*  Calcula a frequencia de cada caracter
* inputs: vetor de frequecias, arquivo entrada
* outputs: nenhuma
* pré-condicao: O vetor de inteiros tem o conteúdo de todas as posições igual a 0
* pós-condicao: o vetor de frequencia deve conter as
frequencias de cada caracter contido no arquivo*/
void frequencia(int*, FILE*);

/* Compara as frequencias entre duas arvores
* inputs: ponteiros void para duas arvores
* outputs: 1 caso a primeira arvore seja maior ou igual a primeira
ou 0 caso a segunda seja maior que a primeira
* pré-condicao: existencia das arvores dadas como paramentro
* pós-condicao: nenhuma*/
int compara_Freq(void*, void*);

/* Gera nome do arquivo compactado
* inputs: nome do arquivo que esta compactado
* outputs: nome do arquivo de saida compactado
* pré-condicao: existencia de um nome do arquivo q esta sendo
compactado
* pós-condicao: nenhuma */
char* nome_Saida(char*);

/* Diz se houve erro na leitura do arquivo
* inputs: arquivo
* outputs: nenhum
* pré-condicao: nenhum
* pós-condicao: caso seja encontrado um erro na leitura
uma mensagem sera exibida e o programa sera parado*/
void Erro(FILE*);

/* Cria lista de caracteres e suas respectivas frequencias em ordem
crescente
* inputs: lista que sera preenchida, vetor de frequecia de caracteres
* outputs: nenhum
* pré-condicao: O vetor de inteiros tem 256 posições e a sentinela da lista deve ter sido inicializada
* pós-condicao: Lista deve estar preenchida com os caracteres e
suas frequencias em ordem crescente */
void cria_Lista_Caracteres(Lista*,int*);

/* Cria arvore de HUffman
* inputs: Lista de caracteres e suas frequecias
* outputs: arvore de huffman, preenchida ou vazia caso a lista
de frequencia esteja vazia
* pré-condicao: Lista genérica já foi preenchida pela função cria_Lista_Caracteres.
* pós-condicao: lista genérica liberada*/
Arv* cria_Arv_Huffman(Lista*);

/* Escreve o cabecalho do arquivo compactado baseado na arvore
de Huffman no bitmap
* inputs: arvore de Huffman, bimap
* outputs: nenhum
* pré-condicao: nenhuma
* pós-condicao: cabecalho escrito no bit map caso a arvore
exista ou nenhuma, caso a arvore de huffman esteja vazia*/
void bitmap_Header(Arv*, bitmap*);

/* Escreve o cabecalho, baseado na arvore de huffman, no
arquivo de saida compactado
* inputs: arvore de HUffman, arquivo que esta compactado
* outputs: nenhuma
* pré-condicao: existencia da arvore de Huffman, o arquivo precisa
ter sido criado para a saida
* pós-condicao: o cabecalho deve ter sido escrito no arquivo de
saida*/
void write_Header(Arv*, FILE*);

/* Escreve os caracteres compactados em binario no arquivo de
saida
* inputs: arvore de Huffman, arquivo de saida compactado,
o arquivo que deve ser compactado, vetor de Hash para a traducao
rapida dos caracteres normais para os compactados
* outputs: nenhuma
* pré-condicao: Árvore de Huffman existe e é a árvore correspondente
ao arquivo de entrada, arquivo de entrada e saída e vetor Hash já existente.
* pós-condicao: Arquivo compactado foi escrito.*/
void escreve_Dados(Arv*,FILE*,FILE*,char**);

/* Criacao, alocamento e preenchimento da tabela Hash
* inputs: Vetor de frequencias de caracteres, arvore de HUffman
* outputs: Tabela Hash preenchida
* pré-condicao: Existencia do vetor de frequencia e da arvore de
Huffman
* pós-condicao: Tabela Hash preenchid */
char** cria_Hash(int* vet, Arv* x);

/*Compacta arquivos
* inputs: Nome do arquivo que deve ser compactado
* outputs: Nenhum
* pré-condicao: Nenhuma
* pós-condicao: arquivo compactado*/
void compactador(char*);

//DESCOMPACTADOR

/* Recontroi arquivo original baseado no arquivo compactado
* inputs: Arvore de Huffman extraida do arquivo compactado, arquivo
compactado, nome do arquivo original, quantidade de bit lixo
no byte final
* outputs: nenhum
* pré-condicao: existencia da arvore, arquivo e nome dado por parametro
* pós-condicao: arquivo original recriado*/
void reconstroi_Arquivo(Arv*, FILE*, char*, int);

/* Carrega um byte do arquivo lido em uma varaivel unsigned char
* inputs: Arquivo de entrada, variavel receptora do byte
* outputs: 1 caso a leitura seja realizada com sucesso e 0 caso contrario
* pré-condicao: Existencia do arquivo dado como paramentro
* pós-condicao: um byte carregado na varaivel unsigned char dada como parametro*/
int carrega_Byte(FILE*, unsigned char *);

/* Reconstroi bitmap baseado nos bits do cabecalho
* inputs: Arquivo de entrada, tamanho do cabecalho em bits
* outputs: bitmap preenchido com os bits do cabecalho
* pré-condicao: nenhuma
* pós-condicao: bitmap criado*/
bitmap remonta_Mapa(FILE*, int);

/* Remonta a arvore de Huffman baseado no cabecalho do arquivo
compactado
* inputs: bitmap, inteiro que sera a posicao percorrida no bitmap
* outputs: arvore criada com os caracteres como folhas
* pré-condicao: existencia do bitmap, inteiro posicao ja no inicio do cabecalho
no inicio da funcao
* pós-condicao: nenhuma */
Arv* remonta_Arvore(bitmap, int*);

/* Apaga o arquivo compactado
* inputs: Nome do arquivo compactado
* outputs: Nenhum
* pré-condicao: Existencia do arquivo compactado
* pós-condicao: O arquivo apagado*/
void delete_Old_File(char*);

/* Extrai o nome original do arquivo da compactacao
* inputs: Nome do arquivo compactado
* outputs: Nome original do arquivo
* pré-condicao: Existencia do nome do arquivo compactado
* pós-condicao: Recriacao do nome do arquivo original*/
char* nome_Original(char*);

/*Descompacta arquivos
* inputs: Nome do arquivo que deve ser descompactado
* outputs: Nenhum
* pré-condicao: Nenhuma
* pós-condicao: O arquivo compactado foi excluído e o arquivo descompactado foi posto no lugar.*/
void descompactador(char*);


#endif
