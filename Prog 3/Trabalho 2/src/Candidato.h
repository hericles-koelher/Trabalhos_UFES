#ifndef CANDIDATO_H_
#define CANDIDATO_H_

#include "Partido.h"

class Candidato {
	string nome;
	int votos;
	Partido* partido;
	bool eleito;

public:
	Candidato(string, int, Partido*, bool);
	Candidato();
	Candidato(const Candidato&);
	const string getNome() const;
	const int getVotos() const;
	const bool isEleito() const;
	const Partido* getPartido() const;
	
	bool operator<(const Candidato&) const;
	
	virtual ~Candidato();
};

#endif