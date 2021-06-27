#include "Partido.h"

Partido::Partido(string nome, Coligacao* c) {
	this->nome = nome;
	total_votos = 0;
	eleitos = 0;
	col = c;
}

Partido::Partido() {
	nome = nullptr;
	col = nullptr;
	eleitos = total_votos = 0;
}

Partido::Partido(const Partido& p) {
	nome = p.nome;
	eleitos = p.eleitos;
	total_votos = p.total_votos;
	col = p.col;
}

const string Partido::getNome() const {return nome;}

const int Partido::getEleitos() const {return eleitos;}

const int Partido::getVotos() const {return total_votos;}

const Coligacao* Partido::getColigacao() const {return col;}

void Partido::addCandidatoData(int votos, bool aux_eleito) {
	total_votos += votos;
	eleitos += aux_eleito;
}

bool Partido::hasColigacao() {return col->getNome().empty();}

bool Partido::operator<(const Partido& p)const {return getVotos() < p.getVotos() ? true : false;}

Partido::~Partido() {}
