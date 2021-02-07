package trab_java;

import java.util.HashSet;
import java.util.Set;

public class Partido implements Comparable<Partido> {
	//Attributes
	private String nome;
	private int total_votos;
	private int eleitos;
	private Set<Candidato> candidatos;
	private Coligacao col;
	
	//Constructor
	public Partido(String nome) {
		//Remove um whitespace do primeiro caracter do nome, caso haja
		if(Character.isWhitespace(nome.charAt(0))) {
			nome = nome.substring(1);
		}
		
		this.nome = nome;
		this.total_votos = 0;
		this.eleitos = 0;
		this.candidatos = new HashSet<Candidato>();
		this.col = null;
	}
	
	//Getters
	public String getNome() {
		return this.nome;
	}
	
	public int getEleitos() {
		return this.eleitos;
	}
	
	public int getVotos() {
		return this.total_votos;
	}
	
	public Coligacao getColigacao() {
		return this.col;
	}
	
	//Setters
	public void setColigacao(Coligacao c) {
		this.col = c;
	}
		
	//Methods
	public void addCandidato(Candidato x) {
		//Adiciona um candidato 'x' ao partido, e incrementa as contagens de votos
		this.candidatos.add(x);
		this.total_votos += x.getVotos();
		this.col.addVotos(x.getVotos());
		
		//Se esse candidato tiver sido eleito, incrementa o nº de eleitos do partido e da coligação
		if (x.isEleito()) {this.eleitos++; this.col.addEleito();}
	}

	public boolean hasColigacao() {
		return this.col!=null;
	}
	
	public int qtddCandidatos() {
		return this.candidatos.size();
	}

	@Override
	public String toString() {
		String txt = this.nome;
		
		txt += ", " + this.total_votos + " votos, " + this.eleitos;
		
		if (this.eleitos > 1) txt += " candidatos eleitos";
		else txt += " candidato eleito";
		
		return txt;
	}

	@Override
	public int compareTo(Partido x) {
		return x.getVotos() - this.getVotos();
	}
}
