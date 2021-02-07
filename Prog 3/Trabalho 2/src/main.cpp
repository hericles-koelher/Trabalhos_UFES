#include <iostream>
#include <fstream>
#include <algorithm>
#include "Candidato.h"
#include "DadosCSV.h"

ostream& operator<<(ostream& stream, const Candidato& p);
ostream& operator<<(ostream& stream, const Partido& p);
ostream& operator<<(ostream& stream, const Coligacao& p);

int main(int argc, char** argv){

	try{
		//Lê o encode especificado, caso haja, e cria o leitor
		string encode;
		if(argc >= 3)	encode = string(argv[2]);
		else			encode = "pt_BR.UTF-8";

		DadosCSV CSV(argv[1], encode);

		//Listas utilizadas para armazenar os dados que serão computados para o relatorio
		vector<Partido*> partidos;
		vector<Candidato> candidatos;
		vector<Coligacao*> coligacoes;

		CSV.getNextLine();	//Ignora a primeira linha

		while(CSV.getNextLine()){

			//Busca uma coligação na lista de coligações e retorna um iterador para o elemento caso encontre,
			//ou um iterador para o final do vector caso não encontre
			vector<Coligacao*>::iterator c2;
			c2 = find_if_not(coligacoes.begin(), coligacoes.end(), 	[&] (Coligacao* c) -> bool{
																		return c->getNome().compare(CSV.getNomeColigacao());
																	});

			Coligacao* c;
			if(c2 == coligacoes.end()){
				c = new Coligacao(CSV.getNomeColigacao());
				coligacoes.push_back(c);
			}else{
				c = *c2;
			}

			//Busca um partido na lista de partidos e retorna um iterador para o elemento caso encontre,
			//ou um iterador para o final do vector caso não encontre
			vector<Partido*>::iterator p2;
			p2 = find_if_not(partidos.begin(), partidos.end(), 	[&] (Partido* p) -> bool{
																	return p->getNome().compare(CSV.getNomePartido());
																});
			Partido* p;
			if(p2 == partidos.end()){
				p = new Partido(CSV.getNomePartido(),c);
				partidos.push_back(p);
			}else{
				p = *p2;
			}

			//Cria um objeto da classe candidato
			Candidato ca = Candidato(CSV.getNome(), CSV.getVotos(), p, CSV.getStatus());
			candidatos.push_back(ca);
		}

		for(Coligacao* c : coligacoes) c->addPartidos(&partidos);

		//Ordenação dos vectors
		sort(partidos.begin(),   partidos.end(),   [] (Partido* x, Partido* y) 	   {return *y < *x;});
		sort(candidatos.begin(), candidatos.end(), [] (Candidato x, Candidato y)   {return  y <  x;});
		sort(coligacoes.begin(), coligacoes.end(), [] (Coligacao* x, Coligacao* y) {return *y < *x;});

		//Inicia as stringsstream's de saida
		stringstream eleitos, mais_votados, quase_eleitos, eleitos_prop, colig, part;

		eleitos << "Vereadores eleitos:\n";
		mais_votados << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):\n";
		quase_eleitos << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n(com sua posição no ranking de mais votados)\n";
		eleitos_prop << "Eleitos, que se beneficiaram do sistema proporcional:\n(com sua posição no ranking de mais votados)\n";
		colig << "Votação (nominal) das coligações e número de candidatos eleitos:\n";
		part << "Votação (nominal) dos partidos e número de candidatos eleitos:\n";

		// Contadores para auxiliar o loop abaixo
		int total_votos = 0, cont = 1, vagas = CSV.getVagas();

		//Varre o conjunto de candidatos, construindo as strings de saída
		for(int i = 0; i < int(candidatos.size()); i++) {

			if(candidatos[i].isEleito()) {
				eleitos << cont++ << " - " << candidatos[i];
			}

			if(i < vagas) {
				mais_votados << i+1 << " - " << candidatos[i];
			}

			if(i < vagas && !candidatos[i].isEleito()) {
				quase_eleitos << i+1 << " - " << candidatos[i];
			}

			if(i >= vagas && candidatos[i].isEleito()) {
				eleitos_prop << i+1 << " - " << candidatos[i];
			}

			total_votos += candidatos[i].getVotos();
		}

		//Alteração da string com os dados das coligações
		cont = 1;
		for(Coligacao* x : coligacoes) colig << cont++ << " - " << *x;

		//Alteração da string com os dados dos partidos
		cont = 1;
		for(Partido* x : partidos) part << cont++ << " - " << *x;

		//Liberação de memória
		for(Coligacao* c : coligacoes)	delete c;
		for(Partido* p : partidos)		delete p;

		//Saida
		cout << "Número de vagas: " << vagas << "\n\n";
		cout << eleitos.str() << '\n';
		cout << mais_votados.str() << '\n';
		cout << quase_eleitos.str() << '\n';
		cout << eleitos_prop.str() << '\n';
		cout << colig.str() << '\n';
		cout << part.str() << '\n';
		cout << "Total de votos nominais: " << total_votos << '\n';

	}catch(exception& e){
		cout << "Erro: " << e.what() << '\n';
		cout << "Provavelmente causado pelo arquivo de entrada.\nEncerrando execução.\n";
	}

	return 0;
}

ostream& operator<<(ostream& stream, const Candidato& p) {
	stream << p.getNome();

	stream << " (" + p.getPartido()->getNome() << ", " << p.getVotos() << " votos)";

	if(p.getPartido()->getColigacao()->nPartidos() > 1) {
		stream << " - Coligação: " << p.getPartido()->getColigacao()->getNome();
	}

	return stream << '\n';
}

ostream& operator<<(ostream& stream, const Partido& p) {
	stream << p.getNome();

	stream << ", " << p.getVotos() << " votos, " << p.getEleitos();

		if (p.getEleitos() > 1)	stream << " candidatos eleitos";
		else 					stream << " candidato eleito";

	return stream << '\n';
}

ostream& operator<<(ostream& stream, const Coligacao& c){
	stream << "Coligação: ";

	stream << c.getNome() <<  ", " << c.getVotos() << " votos, " << c.nEleitos();

	if (c.nEleitos() > 1) 	stream << " candidatos eleitos";
	else 					stream << " candidato eleito";

	return stream << '\n';
}
