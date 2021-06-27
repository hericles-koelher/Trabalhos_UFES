namespace Relatorio_das_Eleições
{
    public class Candidato
    {
        // Abaixo todas temos atributos privados e propriedades publicas.
        // Propriedades são maneiras mais simples e elegantes de utilizar 
        // os classicos metodos get e set.
        
        // Propridades com o formato: public type propertyName => privateVar
        // são propriedades compostas unicamente pelo metodo get.
        private readonly string _nome;
        
        public bool FoiEleito { get; }
        
        public int Votos { get; }

        private readonly Partido _partido;
        public Partido PartidoCandidato => _partido;

        public Candidato(string nome, Partido partido, int votos, bool foiEleito)
        {
            _nome = nome;
            Votos = votos;
            FoiEleito = foiEleito;
            _partido = partido;
            partido.AdicionarCandidato(this);
        }

        public override string ToString()
        {
            string resultado = $"{_nome} ({_partido.Nome}, {Votos} votos)";

            if (!_partido.Coligacao.Equals(""))
            {
                resultado += $" - Coligação: {_partido.Coligacao}";
            }

            return resultado;
        }
    }
}