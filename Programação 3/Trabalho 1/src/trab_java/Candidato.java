package trab_java;

public class Candidato implements Comparable<Candidato> {
	//Attributes
	private String nome;
	private int votos;
	private Partido partido;
	private boolean eleito;
	
	//Constructor
	public Candidato(String nome,int votos, Partido partido, boolean eleito) {
		this.nome = nome;
		this.votos = votos;
		this.partido = partido;
		this.eleito = eleito;
		
		//O candidato é adicionado ao seu partido no momento de sua criação
		partido.addCandidato(this);
	}
		
	//Getters
	public int getVotos() {
		return this.votos;
	}
	
	public boolean isEleito() {
		return this.eleito;
	}
	
	//Methods
	@Override
	public String toString() {
		String txt = this.nome;
		
		txt += " (" + this.partido.getNome() + ", " + this.votos + " votos)";
		
		if( this.partido.getColigacao().tamanho() > 1) txt += " - Coligação: " + this.partido.getColigacao().getNome();
				
		return txt;
	}

	@Override
	public int compareTo(Candidato x) {
		return x.getVotos() - this.getVotos();
	}
}
