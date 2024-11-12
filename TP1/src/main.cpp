#include <iostream>
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/capital.h"

int main(){
  std::unordered_map<std::string, std::vector<std::string>> Grafo;
  
  int numArestas, numVertices;
  std::vector<std::string> PossiveisNovasOrigens;
    
    std::cin >> numVertices >> numArestas;

    for (int i = 0; i < numArestas; ++i) {
        std::string origem, destino;
        std::cin >> origem >> destino;

        // Adiciona a aresta de origem para destino com o peso dado
        Grafo[origem].emplace_back(destino);
        PossiveisNovasOrigens.push_back(destino);
    } 

    // Garantir que todos os vértices, incluindo destinos, existam no grafo
    for (int i = 0; i < PossiveisNovasOrigens.size(); i++){
        const std::string& vertice = PossiveisNovasOrigens[i];
        if (Grafo.find(vertice) == Grafo.end()) {
            // Se o vértice não existe, cria com uma lista vazia de vizinhos
            Grafo[vertice] = {};
        }
    } 
   
    std::string resultado = Capital(Grafo);

    std::cout << resultado << std::endl; 

    return 0;
}