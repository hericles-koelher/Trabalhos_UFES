//
// Created by bruno on 11/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

void closePipes(int*, int*, int*);

const char fmt[] = "Meu filho, crie e envie para o seu irmão um array de números inteiros com valores randômicos entre 1 e %d. O tamanho do array também deve ser randômico, na faixa de 1 a 10.";

int main(){
    int x;

    do{
        printf("Informe um número entre 1 e 5\n");
        scanf("%d", &x);
    }while (x < 1 || x > 5);

    int fd1[2], fd2[2], fd3[2];
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);

    int pid1 = fork();

    if (pid1 == -1){
        fprintf(stderr, "Falha ao executar fork\n");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0){
        int valueOfX, msgSize;

        //Leitura de x e msgSize
        read(fd1[0], &valueOfX, sizeof(valueOfX));
        read(fd1[0], &msgSize, sizeof(msgSize));

        char msg[200];

        read(fd1[0], msg, msgSize);

        //Colocando \0 na ultima posição da string
        msg[(msgSize/sizeof(char))] = '\0';

        printf("\n%s\n", msg);

        //Criando array de tamanho aleatório e preechendo
        int numberOfElements, array[10];

        srand(time(NULL));
        numberOfElements = (rand() % 10) + 1;

        for(int i = 0; i < numberOfElements; i++)
            array[i] = (rand() % valueOfX) + 1;


        write(fd2[1], &numberOfElements, sizeof(int ));
        write(fd2[1], array, sizeof(int) * numberOfElements);

        //Fechando pipes
        closePipes(fd1, fd2, fd3);

        return 0;
    }else{
        //Coloquei dentro do else só pra não me perder/confundir :)
        //Enviando valor de x
        write(fd1[1], &x, sizeof(x));

        //Formatação da mensagem
        char msg[200];
        sprintf(msg, fmt, x);

        int msgSize = strlen(msg) * sizeof(char);

        //Escrevendo tamanho da messagem a seguir
        write(fd1[1], &msgSize, sizeof(msgSize));
        //Escrevendo a mensagem
        write(fd1[1], msg, msgSize);
    }

    int pid2 = fork();

    if (pid2 == -1){
        fprintf(stderr, "Falha ao executar fork\n");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0){
        int value, numberOfElementsInArray, array[10], sum = 0;

        //Leitura de valores
        read(fd2[0], &value, sizeof(value));
        read(fd2[0], &numberOfElementsInArray, sizeof(numberOfElementsInArray));
        read(fd2[0], array, sizeof(int) * numberOfElementsInArray);

        //Soma
        for(int i = 0; i < numberOfElementsInArray; i++)
            sum += array[i];

        //Enviando a p0 o resultado da soma
        write(fd3[1], &sum, sizeof(int));

        //Fechando pipes
        closePipes(fd1, fd2, fd3);

        return 0;
    }else{
        //Coloquei dentro do else só pra não me perder/confundir :)
        //Enviando o valor ao p2
        write(fd2[1], &x, sizeof(x));

        int sum;

        read(fd3[0], &sum, sizeof(int));

        printf("\nA soma é %d\n", sum);

        //Fechando pipes
        closePipes(fd1, fd2, fd3);
    }

    while (waitpid(-1, NULL, WNOHANG) != -1);

    int pid3 = fork();

    if (pid3 == -1){
        fprintf(stderr, "Falha ao executar fork\n");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0){
       int fileId = open("PipePing.txt", O_WRONLY | O_CREAT, 0777);

        dup2(fileId, STDOUT_FILENO);

        char *arr[5] = {"ping", "-c", "5", "ufes.br", NULL};

        execvp(arr[0], arr);
    }

    return 0;
}

void closePipes(int* a, int* b, int* c){
    for(int i = 0; i < 2; i++){
        close(a[i]);
        close(b[i]);
        close(c[i]);
    }
}