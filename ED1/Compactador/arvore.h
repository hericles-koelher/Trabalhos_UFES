#include <stdlib.h>
#include <stdio.h>

typedef struct arv Arv;

/*Cria uma arvore vazia
* inputs: Nada
* outputs: NULL
* pré-condicao: nenhuma
* pós-condicao: nenhuma*/
Arv* arv_criavazia (void);

/*Cria arvore com os dados passados
* inputs: letra que sera guardada, contador de frequencia da letra, arvore filha
a esquerda, arvore filha a direita
* outputs: arvore criada com os parametros passados
* pré-condicao: nenhuma
* pós-condicao: uma arvore craida*/
Arv* arv_cria (unsigned char,int , Arv*, Arv*);

/*LIbera arvore
* inputs: arvore que deve ser liberada
* outputs: NULL
* pré-condicao: nenhuma
* pós-condicao: arvore ter sido liberada*/
Arv* arv_libera (Arv* a);

/*Checa se a arvore é vazia
* inputs: arvore que sera checada
* outputs: 0 caso a arvore não seja vazia e 1 caso seja
* pré-condicao: nenhuma
* pós-condicao: nenhuma*/
int arv_vazia (Arv* a);

/*Checa se um determinado caracter esta na arvore
* inputs: arvore que sera checada, caracter que sera procurado
* outputs: 0 caso o caraccter não esteja na arvore e 1 caso esteja
* pré-condicao: nenhuma
* pós-condicao: nenhuma*/
int arv_Pertence_Folha (Arv* a, unsigned char c);

/*Imprime arvore
* inputs: arvore
* outputs: nada
* pré-condicao: nenhuma
* pós-condicao: arvore ter sido impressa*/
void arv_imprime (Arv* a);

/*Retorna o conteudo do campo info do nó
* inputs: arvore
* outputs: conteudo do campo info
* pré-condicao: o campo info conter algum conteudo
* pós-condicao: nenhum*/
unsigned char info (Arv* a);

/*Retorna o campo cont do no da arvore
* inputs: arvore
* outputs: conteudo do cant
* pré-condicao: o campo cont conter algum conteudo
* pós-condicao: nenhuma */
int numero_Frequencia(Arv* x);

/* Ira gerar o codigo do caracter na arvore de huffman
* inputs: arvore percorrida, caracter buscado,vetor do codigo gerado
para o caracter, posicao que sera preenchida no codigo
* outputs: nenhum
* pré-condicao: existencia da arvore dada como parametro
* pós-condicao: codigo do caracter encontrado*/
void gera_Codigo_Char(Arv*, unsigned char, char*, int);

/* Retornar os filhos da arvore dada
* inputs: arvore, inteiro que indica qual filho retornar
* outputs: filho da esquerda caso a entrada seja 0, filho da direita
caso a entrada seja 1
* pré-condicao: arvore dada não ser vazia
* pós-condicao: nenhuma */
Arv* caminhar(Arv*, int);

/* Retorna a altura da arvore
* inputs: arvore
* outputs: altura da arvore
* pré-condicao: nenhuma
* pós-condicao: nenhuma */
int altura(Arv*);

/* Diz se a arvore e folha
* inputs: arvore
* outputs: 0 se não for folha, 1 se for folha
* pré-condicao: arvore não ser vazia
* pós-condicao: nenhuma*/
int ehFolha(Arv *);
