//
// Created by Bruno on 01/12/2020.
//

#include "MonitorBanheiro.h"
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>

//Utilizado para controlar a quantidade de pessoas no banheiro/fila.
int corintianosNoBanheiro = 0;
int corintianosApertados = 0;
int palmeirensesNoBanheiro = 0;
int palmeirensesApertados = 0;

typedef enum{
    Corinthians,
    Palmeiras,
    Nenhum
}timeDeFutebol;

//Flag utilizada para definir tipo de usuário atual do banheiro.
timeDeFutebol timeNoBanheiro = Nenhum;

//Inicializando mutex e cond
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condCor = PTHREAD_COND_INITIALIZER;
pthread_cond_t condPalm = PTHREAD_COND_INITIALIZER;
pthread_cond_t condFila = PTHREAD_COND_INITIALIZER;

//Utilizado para simular prioridade do corintiano no uso do banheiro.
bool corintianoQuerUsar = false;

void corintianoQuerEntrar(){
    pthread_mutex_lock(&lock);

    //Travando a entrada de novos palmeirenses (visto que os corintianos tem prioridade no uso do banheiro).
    corintianoQuerUsar = true;

    //Verificando se a posse do banheiro ainda pertence ao outro time
    //Caso sim aguarda pelo ultimo palmeirense se retirar do banheiro.
    if (timeNoBanheiro == Palmeiras){
        pthread_cond_wait(&condCor, &lock);
    }

    //Nessa parte timeNoBanheiro é "Nenhum" ou já é "Corinthians".
    timeNoBanheiro = Corinthians;

    //Representa o número de corintianos na fila + os que já estão no banheiro.
    corintianosApertados++;

    //Aguardando caso não tenha cabines disponiveis.
    if (corintianosApertados > 3)
        pthread_cond_wait(&condFila, &lock);

    corintianosNoBanheiro++;

    printf("Corintianos: %d\nPalmeirenses: %d\n\n", corintianosNoBanheiro, palmeirensesNoBanheiro);

    pthread_mutex_unlock(&lock);
}

void corintianoSai(){
    pthread_mutex_lock(&lock);

    //"Liberando uma cabine".
    corintianosNoBanheiro--;
    corintianosApertados--;

    //Libera o banheiro para qualquer time que por ventura queira utilizar
    //OBS: Libera caso não existam corintianos usando ou querendo usar o banheiro.
    if (corintianosNoBanheiro == 0 && corintianosApertados == 0){
        corintianoQuerUsar = false;
        timeNoBanheiro = Nenhum;
        pthread_cond_broadcast(&condPalm);
    }
    else{
        //Chama o proximo corintiano da fila (se alguem estiver esperando).
        pthread_cond_signal(&condFila);
    }

    pthread_mutex_unlock(&lock);
}

void palmeirenseQuerEntrar(){
    pthread_mutex_lock(&lock);

    //Verificando se a posse do banheiro ainda pertence ao outro time
    //Caso sim aguarda pelo ultimo corintiano se retirar do banheiro.
    if (timeNoBanheiro == Corinthians)
        pthread_cond_wait(&condPalm, &lock);

    //Força as novas threads a esperarem se um corintiano solicitou o banheiro.
    if(corintianoQuerUsar)
        pthread_cond_wait(&condPalm, &lock);

    //Nessa parte timeNoBanheiro ou é "Nenhum" ou já é "Palmeiras".
    timeNoBanheiro = Palmeiras;

    //Representa o número de corintianos na fila + os que já estão no banheiro.
    palmeirensesApertados++;

    //Aguardando caso não tenha cabines disponiveis.
    if (palmeirensesApertados > 3)
        pthread_cond_wait(&condFila, &lock);

    palmeirensesNoBanheiro++;

    printf("Corintianos: %d\nPalmeirenses: %d\n\n", corintianosNoBanheiro, palmeirensesNoBanheiro);

    pthread_mutex_unlock(&lock);
}

void palmeirenseSai(){
    pthread_mutex_lock(&lock);

    //"Liberando uma cabine".
    palmeirensesNoBanheiro--;
    palmeirensesApertados--;

    //Libera o banheiro para qualquer time que por ventura queira utilizar
    //OBS: Libera caso não existam palmeirenses usando ou querendo usar o banheiro.
    if (palmeirensesNoBanheiro == 0 && palmeirensesApertados == 0){
        timeNoBanheiro = Nenhum;
        pthread_cond_broadcast(&condCor);
    }
    else{
        //Chama o proximo palmeirense da fila (se alguem estiver esperando).
        pthread_cond_signal(&condFila);
    }

    pthread_mutex_unlock(&lock);
}