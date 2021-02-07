package trab_java;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Set;

public class Coligacao implements Comparable<Coligacao> {
	//Attributes
	private Set<Partido> col;
	private String nome;
	private int votos;
	private int eleitos;
	
	//Constructor
	public Coligacao(String pNomes, LinkedList<Partido> partidos) {
		
		//Inicializa os valores base
		this.votos = 0;
		this.eleitos = 0;
		this.col = new HashSet<Partido>();
		
		//Remove o whitespace do início do nome dos partidos, caso haja
		if(Character.isWhitespace(pNomes.charAt(0))) {
			pNomes = pNomes.substring(1);
		}
		
		//O nome da coligação é o nome dos partidos que a compõe
		this.nome = pNomes;
		
		//Isola cada nome da string de nomes de partidos
		String[] aux = pNomes.split("/");
		
		//Varre todos os nomes dos partidos dessa coligação
		for(int i = 0; i < aux.length; i++) {
			//flag para saber se precisa criar o partido ou não
			boolean ok = false;
			
			//Varre todos os partidos criados, e ao encontrar faz a ligação entre ele e a coligação
			for(Partido x: partidos) {
				if(x.getNome().replaceAll(" ", "").equals(aux[i].replaceAll(" ", ""))) {
					addPartido(x);
					x.setColigacao(this);
					ok = true;
					break;
				}
			}
			//Caso não tenha achado o partido, cria o partido e faz a ligação
			if(!ok) {
				//Corrige o nome, removendo o whitespace do início, caso haja
				if(Character.isWhitespace(aux[i].charAt(0))) {
					aux[i] = aux[i].substring(1);
				}
				Partido novo = new Partido(aux[i]);
				addPartido(novo);
				partidos.add(novo);
				novo.setColigacao(this);
			}
		}
	}
	
	//Getters
	public int getVotos() {
		return votos;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public int nEleitos() {
		return eleitos;
	}

	//Methods
	public void addVotos(int n) {
		this.votos += n;
	}
	
	public void addEleito() {
		eleitos++;
	}
	
	public int tamanho() {
		return this.col.size();
	}
	
	public void addPartido(Partido p) {
		this.col.add(p);
	}
	
	@Override
	public String toString() {
		String txt = "Coligação: ";
		
		txt += this.getNome() + ", " + this.getVotos() + " votos, " + this.nEleitos();   
		
		if (this.nEleitos() > 1) txt += " candidatos eleitos";
		else txt += " candidato eleito";
		
		return txt;
	}
	
	@Override
	public int compareTo(Coligacao x) {
		return x.getVotos() - this.getVotos();
	}
}
