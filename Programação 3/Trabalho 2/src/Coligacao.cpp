#include "Coligacao.h"
#include "Utilitarios.h"
#include <algorithm>

Coligacao::Coligacao(string nome) {
	this->nome = nome;
}

Coligacao::Coligacao() {
	nome = nullptr;
}

Coligacao::Coligacao(const Coligacao& c) {
	nome = c.nome;
	partidos = c.partidos;
}

const string Coligacao::getNome() const {return nome;}

const int Coligacao::getVotos() const {
	int votos = 0;

	for(unsigned x = 0; x < partidos.size(); x++) votos += partidos[x]->getVotos();

	return votos;
}

const int Coligacao::nEleitos() const {
	int eleitos = 0;

	for(unsigned x = 0; x < partidos.size(); x++) eleitos += partidos[x]->getEleitos();

	return eleitos;
}

bool Coligacao::operator<(const Coligacao& c) const {
	return getVotos() < c.getVotos() ? true : false;
}

const int Coligacao::nPartidos() const{
	return partidos.size();
}


void Coligacao::addPartidos(vector<Partido*>* p) {

	vector<string> aux = split(nome," / ");

	for(string x : aux) {
		for(Partido* y : *p) {
			if(!y->getNome().compare(x)) {
				if(none_of(partidos.begin(), partidos.end(), [&](Partido* j) {return y == j;})) {
					partidos.push_back(y);
					break;
				}
			}
		}
	}
}

vector<Partido*> Coligacao::getPartidos() const {return partidos;}

Coligacao::~Coligacao() {}
