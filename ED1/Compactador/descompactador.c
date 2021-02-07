#include "Trabalho2.h"

bitmap remonta_Mapa(FILE* entrada, int n){
    bitmap bm = bitmapInit(n);
    int cont = 0;
    unsigned char byte;

    while(cont != n){
        carrega_Byte(entrada,&byte);
        for(int i = 7; i >= 0; i--){
            bitmapAppendLeastSignificantBit(&bm,0x01 & (byte >> i));
            cont++;
            if(cont == n){
                break;
            }
        }
    }

    return bm;
}

Arv* remonta_Arvore(bitmap bm, int *posicao){
    if(bitmapGetBit(bm, *posicao) == 0){
        unsigned char aux=0;
        *posicao+=1;
        for(int i=7; i >= 0; i--){
            aux = aux | (bitmapGetBit(bm,*posicao) << i);
            *posicao+=1;
        }
        return arv_cria(aux,0,arv_criavazia(),arv_criavazia());
    }

    *posicao+=1;

    Arv *esq = remonta_Arvore(bm,posicao);
    Arv *dir = remonta_Arvore(bm,posicao);

    return arv_cria('*',0,esq,dir);
}

void delete_Old_File(char *nome_Arquivo){

    char *comando = (char*)malloc(sizeof(char)*(7+strlen(nome_Arquivo)));

    strcpy(comando,"rm -rf ");
    strcat(comando,nome_Arquivo);
    system(comando);

    free(comando);
}

void descompactador(char* nome_Arquivo){

    if(nome_Arquivo[strlen(nome_Arquivo)-1] != 'D' || nome_Arquivo[strlen(nome_Arquivo)-2] != 'E'){
        printf("O arquivo deve ter extensão .ED\nFinalizando execução.\n");
        exit(1);
    }

    FILE * entrada=fopen(nome_Arquivo,"rb");
    Erro(entrada);

    int bits_Lixo = fgetc(entrada) , n ,posicao=0;

    fread(&n,sizeof(short int),1,entrada);

    bitmap bm = remonta_Mapa(entrada,n*8);

    Arv *arvore=remonta_Arvore(bm,&posicao);

    reconstroi_Arquivo(arvore,entrada,nome_Arquivo,bits_Lixo);

    arv_libera(arvore);

    delete_Old_File(nome_Arquivo);

}


int carrega_Byte(FILE* entrada, unsigned char *x){
    return fread(x,sizeof(unsigned char),1,entrada) == 1 ? 1:0;
}

void reconstroi_Arquivo(Arv* x, FILE* entrada,char *nome_Arquivo, int bits_Lixo){
    FILE *saida = fopen(nome_Original(nome_Arquivo),"wb");
    int  flag;
    Arv* aux=x;
    unsigned char byte,prox_Byte,caracter;

    //sinaliza se o arqruivo acabou ou não
    flag = carrega_Byte(entrada,&byte);

    //Ira percorrer todo o arquivo e parar quando flag == 0
    while(flag){

        flag = carrega_Byte(entrada,&prox_Byte);

        //le todo os bits do arquivo, caso o arquivo tenha acabado (flag == 0)
        //possivelmente haveram bits lixo no ultimo byte do arquivo compactado
        //tais bits nao serao lidos
        for(int i=0; i < 8-(bits_Lixo*(!flag)); i++){

            //usa dos bits exetraidos do arquivo compactado para
            //encontrar a folhas
            aux = caminhar(aux,(byte >> (7-i)) & 0x01);

            //quando uma folha é encontrada o caracter nela contido
            //deve ser escrito no arquivo descompactado
            if(ehFolha(aux)){

                caracter = info(aux);

                fwrite(&caracter,sizeof(unsigned char),1,saida);

                //a arvore voltara a raiz, pois, inicialmente, se deve partir
                //da raiz para se encontrar as folhas
                aux = x;

            }

        }

        //quando o byte acabar de ser lido um proximo byte deverá ser analizado
        byte = prox_Byte;

    }

    //o arquivo de saida ja foi terminado e deve ser fechado
    fclose(saida);
}

char *nome_Original(char* nome_Arquivo){
    int i = strlen(nome_Arquivo) - 3;
    char *nome = (char*)malloc(sizeof(char)*i);

    for(int j = 0; j < i; j++){
        nome[j] = nome_Arquivo[j];
    }

    nome[i] = '\0';

    return nome;
}
