#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/capital.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/batalhao.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/patrulha.h"

int main() {
    std::unordered_map<std::string, std::vector<std::string>> Grafo;
    int numVertices, numArestas;
    std::vector<std::string> PossiveisNovasOrigens;

    // Lê o número de vértices e arestas do grafo
    std::cin >> numVertices >> numArestas;

    // Lê as arestas e constrói o grafo
    for (int i = 0; i < numArestas; ++i) {
        std::string origem, destino;
        std::cin >> origem >> destino;

        // Adiciona a aresta de origem para destino
        Grafo[origem].emplace_back(destino);
        PossiveisNovasOrigens.push_back(destino);
    }

    // Garante que todos os vértices, incluindo destinos, existam no grafo
    for (const auto& vertice : PossiveisNovasOrigens) {
        if (Grafo.find(vertice) == Grafo.end()) {
            Grafo[vertice] = {}; // Adiciona o vértice com uma lista vazia de vizinhos
        }
    }

    // Encontra a "capital" (vértice com a maior distância)
    std::string resultado = Capital(Grafo);
    std::cout << resultado << std::endl;

    // Vetor para armazenar os componentes fortemente conexos
    std::vector<std::vector<std::string>> componentes;

    // Calcula o número de componentes fortemente conexos usando o algoritmo de Kosaraju
    int qtd_batalhoes = Kosaraju(Grafo, componentes);

    // Exibe o número de batalhões, ou 0 se houver 1 ou menos
    if (qtd_batalhoes <= 1) {
        std::cout << "0" << std::endl;
    } else {
        std::cout << qtd_batalhoes - 1 << std::endl;
    }

    std::vector<std::string> batalhoes;
    
    // Realiza a busca por BFS para encontrar os batalhões adicionais a partir da capital
    for (const auto& componente : componentes) {
        // Encontra o batalhão adicional para o componente atual
        std::string batalhao_adicional = Batalhaoadicional(resultado, Grafo, componente);
        
        // Adiciona o batalhão à lista de batalhões
        batalhoes.push_back(batalhao_adicional);

        // Exibe o batalhão adicional, se for diferente da capital
        if (batalhao_adicional != resultado) {
            std::cout << batalhao_adicional << std::endl;
        }
    }

    // Encontra e exibe os patrulhamentos em cada subgrafo
    rodarDFSNosSubgrafos(Grafo, componentes, batalhoes);

    return 0;
}
