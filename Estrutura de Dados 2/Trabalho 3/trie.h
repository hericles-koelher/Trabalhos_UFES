#ifndef TRIE_H_
#define TRIE_H_

#include "key.h"

typedef struct trie Trie;
typedef unsigned char uchar;

//Inicializa uma trie vazia
Trie* init_trie();

//Insere uma string na trie
void insert_trie(Trie* pai, char* nome, Key T[N]);

//Libera a memória da trie
Trie* destroy_trie(Trie* rip);

#endif // TRIE_H_
