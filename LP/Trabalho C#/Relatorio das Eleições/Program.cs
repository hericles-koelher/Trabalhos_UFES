using System;
using System.Collections.Generic;
using System.Linq;

namespace Relatorio_das_Eleições
{
    class Program
    {
        static void Main()
        {
            LinkedList<Candidato> candidatos = new LinkedList<Candidato>();
            LinkedList<Partido> partidos = new LinkedList<Partido>();

            // using nesse contexto é equivalente aos blocos try/finally
            // para utilizar variaveis junto a esse comando é necessário que eles implementem
            // a interface IDisposable
            using (ColetaDadosCsv dados = new ColetaDadosCsv("Input/divulga.csv"))
            {
                DadosLinha dadosLinha;
                
                // Atribuições em C# são expressões, assim como em C, ou seja, ao executar
                // o trecho abaixo dadosLinha recebe dados.ReadLine() e ainda retorna o objeto
                // para ser avaliado como expressão. Quando isso acontece é solicitado a execução 
                // do metodos Equals para comparar o objeto adquirido com um objeto padrão que indica
                // a ausencia de dados.
                while (!(dadosLinha = dados.ReadLine()).Equals(ColetaDadosCsv.SemDados))
                {
                    // Abaixo uma busca feita usando programação funcional presente no modulo Linq, que retorna
                    // um objeto do tipo WhereEnumerableIterator, que implementa a interface IEnumerable.
                    // Pelo funcionamento de interfaces como classes abstratas puras, elas possibilitam
                    // o trecho de código abaixo, que define um tipo a partir da interface IEnumerable<T>.
                    IEnumerable<Partido> partidosComNomeDesejado =  from pt in partidos 
                                                                    where pt.Nome.Equals(dadosLinha.PartidoCandidato)
                                                                    select pt;

                    // Como sempre teremos exatamente um partido para cada nome, teremos apenas um elemento
                    // na coleção partidosComNomeDesejado.
                    // O método FirstOrDefault sempre retorna o primeiro elemento presente na lista ou null.
                    Partido partido = partidosComNomeDesejado.FirstOrDefault();

                    if (partido == null)
                    {
                        partido = new Partido(dadosLinha.PartidoCandidato, dadosLinha.ColigacaoCandidato);
                        partidos.AddFirst(partido);
                    }
                    
                    Candidato candidato = new Candidato(dadosLinha.Nome, partido, dadosLinha.TotalVotos, dadosLinha.FoiEleito);

                    candidatos.AddFirst(candidato);
                }
            }

            // Algumas funções lambda abaixo
            IEnumerable<Candidato> candidatosEleitos = from candidato in candidatos
                                                        where candidato.FoiEleito
                                                        select candidato;

            // Total de vagas
            Console.WriteLine($"Número de vagas: {candidatos.Sum((c) => Convert.ToInt16(c.FoiEleito))}\n");
            
            int posicaoNaLista = 1;
            
            // Inicio do relatorio sobre vereadores eleitos
            Console.WriteLine("Vereadores Eleitos:");
            foreach (Candidato vereador in candidatosEleitos.OrderBy((c) => c.Votos).Reverse())
            {
                Console.WriteLine($"{posicaoNaLista} - {vereador}");
                posicaoNaLista++;
            }

            posicaoNaLista = 1;
            
            // Inicio do relatorio sobre a votação de cada partido
            Console.WriteLine("\nVotação (nominal) dos partidos e número de candidatos eleitos:");
            foreach (Partido partido in partidos.OrderBy((p) => p.TotalVotos).Reverse())
            {
                Console.WriteLine($"{posicaoNaLista} - {partido}");
                posicaoNaLista++;
            }
            
            // Total de votos
            Console.WriteLine($"\nTotal de votos nominais: {partidos.Sum((partido) => partido.TotalVotos)}");
            
        }
    }
}