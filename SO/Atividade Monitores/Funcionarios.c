//
// Created by Bruno on 01/12/2020.
//

#include "Funcionarios.h"
#include "MonitorBanheiro.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void thread_corintiano(int *id)  // cada corintiano e palmeirense terá um identificador de 1 a 10
{
    while (true){
        corintianoQuerEntrar();
        printf ("Eu sou corintiano-%d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(1);
        corintianoSai();
        printf ("Eu sou corintiano-%d: ... Estou aliviado! Vou trabalhar!\n",*id);
        sleep(15);
    }
}

void thread_palmeirense(int *id)
{
    while (true){
        palmeirenseQuerEntrar();
        printf ("Eu sou palmeirense-%d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(1);
        palmeirenseSai();
        printf ("Eu sou palmeirense-%d: ... Estou aliviado! Vou trabalhar!\n",*id);
        sleep(15);
    }
}

