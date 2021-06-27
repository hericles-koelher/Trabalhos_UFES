#include "Trabalho2.h"

void frequencia(int* vetor_Frequencias, FILE* entrada){
  unsigned char c;

  //a função fread le o arquivo
  //parametros:
        //char q ira receber a letra
        //tamanho em bytes do q sera lido
        //quantos objetos de mesmo tamanho serão lidos
        //arquivo q sera lido

  while(carrega_Byte(entrada,&c)){
    vetor_Frequencias[(unsigned char)c]++;
  }

  //reseta o ponteiro de leitura do aquivo
  rewind(entrada);
}

void cria_Lista_Caracteres(Lista* x,int* vetor_Frequencias){
    Arv *aux;
  //percorre o vetor q simula a tabela ascii
  //quando a letra referente a posição tiver sido lida
  //o vetor terá um valor diferente de 0 e nesse caso
  //uma arvore vazia será criada com sua raiz a frequecia do caracteres
  //essa nova arvore sera ordenada e posta na lista de arvores dada
  //por parametro
  for(int i=0;i<256;i++){
    if(vetor_Frequencias[i]){
      aux=arv_cria(i,vetor_Frequencias[i],arv_criavazia(),arv_criavazia());
      insertion_Sort(x,aux,compara_Freq);
    }
  }
}

int compara_Freq(void* dado1, void* dado2){
    return numero_Frequencia((Arv*)dado1)<=numero_Frequencia((Arv*)dado2)? 1:0;
}

Arv* cria_Arv_Huffman(Lista* x){

  if(!lista_vazia(x)){
    Arv *aux1, *aux2, *aux3;
    //De duas em duas as frequencias das letras dos arquivos são retiradas
    //e colocadas em uma arvores. Uma terceira arvore recebe a soma das
    //frequencias e as duas arvores anteriores como filhas.
    //Depois a nova arvore criada é colocada na lista original na posição
    //q lhe convem numa ordem crescente de frequencia.
    while(tam_Lista(x) > 1){
      aux1=(Arv*)retira_Topo(x);
      aux2=(Arv*)retira_Topo(x);
      aux3=arv_cria('*',numero_Frequencia(aux1)+numero_Frequencia(aux2),aux1,aux2);

      insertion_Sort(x,aux3,compara_Freq);

    }

    aux3=(Arv*)retira_Topo(x);
    libera_lista(x);
    return aux3;
  }
  return NULL;
}

void bitmap_Header(Arv* arvore, bitmap* bit){
    if(!arv_vazia(arvore)){
        if(ehFolha(arvore)){
            bitmapAppendLeastSignificantBit(bit, '0');

            for(int i = 7; 0 <= i; i --)
                bitmapAppendLeastSignificantBit(bit, (info(arvore) >> i) & 0x01);

        }else{
            bitmapAppendLeastSignificantBit(bit, '1');
            bitmap_Header(caminhar(arvore,0), bit);
            bitmap_Header(caminhar(arvore,1), bit);
        }
    }
}

void write_Header(Arv* arvore, FILE* saida){
    //Variavel para acumular o tamanho do cabeçalho.
    //Tal informção é relevante para saber ate qual byte do arquivo compactado
    //o cabeçalho foi representado
    short int nBytesCabecalho;
    //Pega o numero de bits necessario para o cabeçlho e escreve esses
    //bits no bitmap

    bitmap bit=bitmapInit(2559);

    bitmap_Header(arvore,&bit);

    nBytesCabecalho = (bitmapGetLength(bit)/8) + ((bitmapGetLength(bit)%8) == 0? 0:1);

    //Caso o numero de bits não seja multiplo de 8 é necessario somar 1
    //pois a divisão por 8 arredonda o resultado para baixo e isso n pode
    //acontecer pois na leitura do cabeçalho o ultimo byte seria ignorado

    fwrite(&nBytesCabecalho, sizeof(short int) , 1, saida);
    fwrite(bitmapGetContents(bit) , sizeof(unsigned char), nBytesCabecalho, saida);

    free(bitmapGetContents(bit));
}

void escreve_Dados(Arv* x,FILE* saida,FILE* entrada, char **Hash){
    //move o ponteiro o tamanho de um int a partir do inicio do arquivo
    fseek(saida, sizeof(unsigned char), SEEK_SET);
    //bits irrelevantes do ultimo byte do arquivo compactado
    int bits_Lixo=0;

    //Escreve a arvore no arquivo como um cabeçalho no arquivo de saida
    write_Header(x, saida);

    //byte é a Variavel auxiliar que será escrita no arquivo de saida.
    //c é o caracter encontrado durante a leitura do arquivo.
    //bits é autoexplicativo.
    unsigned char c,byte=0;
    int bits=0;

    while(carrega_Byte(entrada,&c)){
        //buffer de tamanho 9 pois caso o codigo de c seja o maior possivel (8) é necessario espaço para o '\0'
        //colocado pela funçao que gera o codigo.
        char buffer[9]={0};

        //gera_Codigo_Char(x,c,buffer,0);

        strcpy(buffer,Hash[c]);

        for(int i=0; fabs(i) < strlen(buffer);i++){

            if(buffer[i] == '1'){
                //equivalente a modificar o valor binario de byte na posicao designada pelo resto da divisao de bits%8 para 1.
                //byte += pow(2,(7-bits%8)); esta forma é equivalente ao treco de codigo abaixo


                byte = byte | 1 << (7-bits%8);

            }
            //atualização do valor de bits já verificados.
            bits++;

            //o bloco abaixo sera executado caso bits%8 seja igual a 0, ou seja, um byte já esta disponivel para escrita.
            if(!(bits%8)){

                fwrite(&byte,sizeof(unsigned char),1,saida);
                //reset da Variavel byte.
                byte=0;
            }
        }
    }

    //escrita do ultimo byte de conteudo relevante caso seja um byte preenchido parcialmente de bits uteis
    if(bits%8){
        bits_Lixo= 7 -(bits%8);
        fwrite(&byte,1,1,saida);
    }
    //move o ponteiro para o inicio do arquivo
    fseek(saida,0,SEEK_SET);
    fwrite(&bits_Lixo,1,1,saida);
}


void compactador(char* nome_Arquivo){
    FILE* entrada=fopen(nome_Arquivo,"rb"), *saida=fopen(nome_Saida(nome_Arquivo),"wb");
    Erro(entrada);

    Lista* caracteres=cria_Lista();
    int vetor_Frequencias[256]={0};

    //Calcula a frequencia de cada caracter no arquivo
    frequencia(vetor_Frequencias,entrada);

    //Cria uma lista ordenada crescente das frequencias dos caracteres
    cria_Lista_Caracteres(caracteres,vetor_Frequencias);

    //cria a arvore de huffman baseada na lista de caracteres ordenados
    Arv* arvore=cria_Arv_Huffman(caracteres);

    char **Hash = cria_Hash(vetor_Frequencias,arvore);

    escreve_Dados(arvore,saida,entrada,Hash);

    fclose(entrada);
    fclose(saida);

    arv_libera(arvore);
}

char* nome_Saida(char* nome_Arquivo){

    int i = strlen(nome_Arquivo);

    char *nome=(char*)malloc(sizeof(char)*(3+i));

    strcpy(nome,nome_Arquivo);

    nome[i] = '.';
    nome[i+1] = 'E';
    nome[i+2] = 'D';

    return nome;
}

void Erro(FILE* arquivo){
    if(!arquivo){
        printf("Arquivo não encontrado\n");
        exit(1);
    }
}

char** cria_Hash(int* vet, Arv* x){
    char **Hash = (char**) malloc(sizeof(char*)*256);
    for(int i = 0; i < 256; i++){
        Hash[i] = (char*) malloc(sizeof(char)*9);
    }

    for(int i = 0; i < 256; i++){
        if(vet[i]){
            gera_Codigo_Char(x,i,Hash[i],0);
        }
    }

    return Hash;
}
