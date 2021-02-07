#include "DadosCSV.h"

DadosCSV::DadosCSV(string filename, string string_locale){
    file = ifstream(filename);
    loc = locale(string_locale);
    vagas = 0;
}

bool DadosCSV::getNextLine(){
    string buffer;

    //Armazena uma linha do arquivo no buffer
    getline(file,buffer,'\n');

    //Verificação do final de arquivo
    if(file.eof()) {return false;}

    //Separação das informações contidas na linha
    vector<string> dados = split(buffer,";");

    //Verifica se o candidato da linha em questão foi eleito e armazena o resultado
    eleito = dados[0][0] == '*';

    vagas += eleito;

    //Nome do candidato em questão
    nome = dados[2];

    //Tratamento do nome do partido e da coligacao
    vector<string> dadosPartido = split(dados[3]," - ");
    partido = dadosPartido[0];
    if(dadosPartido.size() == 1) coligacao = partido;
    else coligacao = dadosPartido[1];

    //Conversão do inteiro que representa o número de votos do candidato
    istringstream conv(dados[4]);
    conv.imbue(loc);
    conv >> votos;

    return true;
}

bool DadosCSV::getStatus() const{return eleito;}

string DadosCSV::getNome() const{return nome;}

string DadosCSV::getNomePartido() const{return partido;}

string DadosCSV::getNomeColigacao() const{return coligacao;}

int DadosCSV::getVotos() const{return votos;}

int DadosCSV::getVagas() const{return vagas;}

DadosCSV::~DadosCSV(){
    file.close();
}
