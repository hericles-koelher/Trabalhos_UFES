#ifndef PARTIDO_H_
#define PARTIDO_H_

#include "Coligacao.h"

using namespace std;

class Coligacao;

class Partido {
	string nome;
	int total_votos, eleitos;
	Coligacao* col;

public:
	Partido(string,Coligacao*);
	Partido(const Partido&);
	Partido();

	const string getNome() const;
	const int getEleitos() const;
	const int getVotos() const;
	const Coligacao* getColigacao() const;
	void addCandidatoData(int,bool);
	bool hasColigacao();
	
	bool operator<(const Partido&) const;
	
	virtual ~Partido();
};

#endif
