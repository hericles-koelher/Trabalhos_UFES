#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include "key.h"

//FUNÇÃO MAIN
int main(int argc, char const *argv[]) {
    //Init I/O
    if (argc != 2) {
        fprintf(stderr, "Usage: ./brute [encrypted password] < [table.txt]\n");
        exit(EXIT_FAILURE);
    }

    Key password = init_key((uchar*)argv[1]);

    //Leitura da tabela
    Key T[N];
    uchar buffer[C+1];     // Buffer temporário.
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        T[i] = init_key(buffer);
    }
    //End I/O
    
    Trie* tr = init_trie();

    /* //TODO
     * Loop que inseriria todas as possibilidades de string na trie 
     * e ao final de cada inserção da string inteira, compararia a
     * chave dessa string com a chave da entrada original.
     * 
     * //? Por quê foi escolhida uma trie:
     * O ganho (possível) de performance se daria na insert_trie e
     * uma possível gestão de memória boa seria liberar a "folha" da
     * trie assim que fosse feita a comparação, e assim sucessivamente
     * para as tries pais, conforme não houvesse mais possibilidades de filhas
    */

    tr = destroy_trie(tr);

    return 0;
}

//* DECLARAÇÃO DO STRUCT TRIE
struct trie {
    int nvl;
    Key value;
    Trie** sons;
};

//* FUNÇÕES ESTÁTICAS
static Trie* create_trie(char index, Key pai, int nvl_pai, Key T[N]) {
    Trie* t = malloc(sizeof(Trie));

    t->value = sum_key_char(pai, index, nvl_pai, T);
    t->sons  = NULL;
    t->nvl   = nvl_pai+1;

    return t;
}

static Trie** init_sons() {
    Trie** vet = malloc(sizeof(Trie*)*32);

        for(int i = 0; i < 32; i++) {
            vet[i] = NULL;
        }

    return vet;
}

static int calc_index(char i) {
    if      (i > 96) return i - 97;
    else if (i > 47) return i - 22;
    else             return -1;
}

//* FUNÇÕES DO .H
Trie* init_trie() {
   Trie* t = malloc(sizeof(Trie));

   t->nvl = 0;
   t->sons = NULL;
   t->value = init_key((uchar*)"");

   return t;
}

void insert_trie(Trie* pai, char* nome, Key T[N]) {
    //Condição de parada da recursão, chegar no fim da string (\0)
    if(nome[0] == '\0') return;

    //Ajuste de char pra indice inteiro, com base 0
    int index = calc_index(nome[0]);

    //Inicializar o vetor de filhos se precisar
    if (pai->sons == NULL) pai->sons = init_sons();

    /* Inicializar o filho, se precisar
     * O ganho de performance (teórico) ocorreria pelo fato de descer
     * na trie não repetir calculo de prefixos de strings iguais!!
     * 
     * Ex.: inserindo "roma" e "romeno", o calculo até "rom" só seria
     * feita uma vez, e essa economia de calculos se torna mais relavante
     * em entradas mais consistentes (mesmos tamanhos, prefixos iguais)
    */
    if (pai->sons[index] == NULL) {
        pai->sons[index] = create_trie(nome[0], pai->value, pai->nvl, T);
    }

    //Passo recursivo
    insert_trie(pai->sons[index], nome+1, T);
}

Trie* destroy_trie(Trie* rip) {
    if(rip == NULL) return NULL;

    if(rip->sons != NULL) {
        for(int i = 0; i < 32; i++) {
            rip->sons[i] = destroy_trie(rip->sons[i]);
        }
    }

    free(rip->sons);
    free(rip);

    return NULL;
}
