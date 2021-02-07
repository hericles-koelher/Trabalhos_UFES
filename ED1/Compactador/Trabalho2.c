#include "Trabalho2.h"

int main(int argc, char** argv){

    if(!strcmp(argv[1],"-c")){
        //autoexplicativo
        compactador(argv[2]);
    }else if(!strcmp(argv[1],"-d")){
        descompactador(argv[2]);
    }else{
        printf("A sintaxe deste compactador/descompactador segue o modelo abaixo:\n\nPara compactar: ./Trabalho -c nomeDoArquivo\n\nPara descompactar: ./betaTrab -d nomeDoArquivo\n\n");
    }

    return 0;
}
