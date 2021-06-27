using System;
using System.IO;

namespace Relatorio_das_Eleições
{
    // Estrutura criada para reunir os dados relevantes do arquivo CSV
    public readonly struct DadosLinha
    {
        public readonly bool FoiEleito;
        public readonly string Nome;
        public readonly string PartidoCandidato;
        public readonly string ColigacaoCandidato;
        public readonly int TotalVotos;

        public DadosLinha(string nomeCandidato, bool foiEleito, int totalVotos, string partido, string coligacao)
        {
            Nome = nomeCandidato;
            FoiEleito = foiEleito;
            TotalVotos = totalVotos;
            PartidoCandidato = partido;
            ColigacaoCandidato = coligacao;
        }
    }
    

    // Esta classe implementa a interface IDisposable com o objetivo de poder 
    // ser utilizada juntamente com o comando using para tornar o gerenciamento do
    // objeto mais simples e legivel.
    public class ColetaDadosCsv : IDisposable
    {
        // Atributo estático utilizado para melhorar legibilidade.
        // Poderia ser substituido por null, mas essa opção é menos legivel. 
        public static readonly DadosLinha SemDados = new DadosLinha();
        
        private bool _disposed;
        private readonly StreamReader _arquivoCsv;

        public ColetaDadosCsv(string caminho)
        {
            if(!File.Exists(caminho)) throw new IOException("Arquivo não encontrado!!!");
            
            _arquivoCsv = new StreamReader(File.Open(caminho, FileMode.Open));
            
            // Ignorando a primeira linha, pois não contem informações uteis
            _arquivoCsv.ReadLine();
        }

        // Este método lê uma linha do arquivo e armazena os dados relevante em uma
        // estrutura do tipo DadosLinha que é retornada ao final.
        public DadosLinha ReadLine()
        {
            string linha = _arquivoCsv.ReadLine();

            if (linha == null) return SemDados;

            string[] dadosLinha = linha.Split(';');

            bool tempEleito = dadosLinha[0][0] == '*';

            string tempNome = dadosLinha[2];
            
            // Split da string com formato: NomePartido - Coligação
            string[] partidoEColigacao = dadosLinha[3].Split(" - ");
          
            string tempPartido = partidoEColigacao[0];
            
            // Em alguns casos o split retorna um array com um elemento, pois
            // não há uma coligação formada pelo partido em questão.
            string tempColigacao = partidoEColigacao.Length > 1 ? partidoEColigacao[1] : "";
            
            // Conversão da string com total de votos. 
            // A string é tratada antes, retirando o ponto presente. 
            int tempVotos = Int32.Parse(dadosLinha[4].Replace(".",""));
            
            // Struct logo abaixo
            DadosLinha dados = new DadosLinha(tempNome, tempEleito, tempVotos, tempPartido, tempColigacao);

            return dados;
        }

        // Os métodos abaixo são exigidos pela interface IDisposable.
        // Dispose é um metodo que "libera" um objeto.
        public void Dispose()
        {
            Dispose(true);
            
            // Pede à VM do .NET (CLR) que não chame o finalizador do objeto especificado
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if(_disposed) return;

            if (disposing) _arquivoCsv.Dispose();

            _disposed = true;
        } 
    }
}