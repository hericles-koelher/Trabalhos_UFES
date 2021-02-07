using System.Collections.Generic;
using System.Linq;

namespace Relatorio_das_Eleições
{
    public class Partido
    {
        // Abaixo todas temos atributos privados e propriedades publicas.
        // Propriedades são maneiras mais simples e elegantes de utilizar 
        // os classicos metodos get e set.
        
        // Propridades com o formato: public type propertyName => privateVar
        // são propriedades compostas unicamente pelo metodo get.
        public string Nome { get; }
        
        public string Coligacao { get; }

        private HashSet<Candidato> _candidatos;

        // Essa propriedade soma os votos de todos os candidatos na lista
        // utilizando o auxilio de uma função lambda.      (x) => x.Valor
        public int TotalVotos => _candidatos.Sum((candidato) => candidato.Votos);

        private int _totalEleitos;

        public Partido(string nome, string coligacao)
        {
            Nome = nome;
            
            Coligacao = coligacao;
            
            _candidatos = new HashSet<Candidato>();
        }

        // Adiciona o candidato à lista encadeada de candidatos do partido & acrescenta um a variavel
        // que contabiliza o total de candidatos eleitos caso seja necessário.
        public void AdicionarCandidato(Candidato candidato)
        {
            _candidatos.Add(candidato);

            if (candidato.FoiEleito)
            {
                _totalEleitos += 1;
            }
        }

        public override string ToString()
        {
            string resultado = $"{Nome}, {TotalVotos} votos, {_totalEleitos}";

            if (_totalEleitos > 1) resultado += " candidatos eleitos";
                else resultado += " candidato eleito";

            return resultado;
        }
    }
}