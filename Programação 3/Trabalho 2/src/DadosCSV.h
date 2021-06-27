#ifndef DADOSCSV_H_
#define DADOSCSV_H_

#include <string>
#include <fstream>
#include <sstream>
#include "Utilitarios.h"

using namespace std;

class DadosCSV{
    ifstream file;
    locale loc;
    bool eleito;
    string nome, partido, coligacao;
    int votos, vagas;

public:
    DadosCSV(string,string);
    bool getStatus()const;
    string getNome()const;
    string getNomePartido()const;
    string getNomeColigacao()const;
    int getVotos()const;
    int getVagas()const;
    bool getNextLine();
    
    virtual ~DadosCSV();

};

#endif
