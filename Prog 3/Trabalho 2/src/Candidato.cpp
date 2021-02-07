#include "Candidato.h"
#include <string>

Candidato::Candidato(string nome, int votos, Partido* p, bool eleito) {
	this->nome = nome;
	this->votos = votos;
	this->eleito = eleito;
	p->addCandidatoData(votos,eleito);
	partido = p;
}

Candidato::Candidato(){
	nome = nullptr;
	votos = 0;
	eleito = false;
	partido = nullptr;
}

Candidato::Candidato(const Candidato& c){
	nome = c.nome;
	votos = c.votos;
	eleito = c.eleito;
	partido = c.partido;
}

const string Candidato::getNome() const {return nome;}

const int Candidato::getVotos() const {return votos;}

const bool Candidato::isEleito() const {return eleito;}

const Partido* Candidato::getPartido() const {return partido;}

bool Candidato::operator<(const Candidato& c) const {
	return getVotos() < c.getVotos() ? true : false;
}

Candidato::~Candidato() {}
