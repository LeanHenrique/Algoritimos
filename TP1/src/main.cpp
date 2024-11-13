#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/capital.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/batalhao.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/patrulha.h"

int main(){
    std::unordered_map<std::string, std::vector<std::string>> Grafo;
    
    int numVertices, numArestas;
    std::vector<std::string> PossiveisNovasOrigens;

    // Lê o número de vértices e arestas
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

    // Chama a função para encontrar a capital
    std::string resultado = Capital(Grafo);
    std::cout << resultado << std::endl;

    // Vetor para armazenar os componentes fortemente conexos
    std::vector<std::vector<std::string>> componentes;

     std::unordered_map<std::string, std::vector<std::string>> regioes;

    // Chama a função para calcular o número de componentes fortemente conexos
    int qtd_batalhoes = Kosaraju(Grafo, componentes);


    // Exibe a quantidade de componentes fortemente conexos ou 0 se for 1 ou menos
    if (qtd_batalhoes <= 1) {
        std::cout << "0" << std::endl;
    } else {
        std::cout << qtd_batalhoes - 1 << std::endl;
    }

     // Realiza o BFS para encontrar o vértice mais próximo em cada componente a partir da capital
    for (const auto& componente : componentes) {
        std::string vertice_mais_proximo = Batalhaoadicional(resultado, Grafo, componente);
        regioes[vertice_mais_proximo].emplace_back(componente);
        for (const auto& vertice : componente) {
        }
        
        if(vertice_mais_proximo != resultado){
        std::cout << vertice_mais_proximo << std::endl;
        }
    }


    return 0;
}
