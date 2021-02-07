#ifndef COLIGACAO_H_
#define COLIGACAO_H_

#include "Utilitarios.h"
#include "Partido.h"
#include <iostream>

using namespace std;

class Partido;

class Coligacao {
	string nome;
	vector<Partido*> partidos;

public:
	Coligacao(string);
	Coligacao();
	Coligacao(const Coligacao&);

	const string getNome() const;
	const int getVotos() const;
	const int nEleitos() const;
	const int tamanho() const;
	const int nPartidos() const;
	vector<Partido*> getPartidos() const;
	void addPartidos(vector<Partido*>*);
	
	bool operator<(const Coligacao&) const;
	
	virtual ~Coligacao();
};

#endif
