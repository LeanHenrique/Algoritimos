#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

int main(){
  std::unordered_map<std::string, std::vector<std::string>> Grafo;
  
  int numArestas, numVertices;
    
    std::cin >> numVertices >> numArestas;

    for (int i = 0; i < numArestas; ++i) {
        std::string origem, destino;
        std::cin >> origem >> destino;

        // Adiciona a aresta de origem para destino com o peso dado
        Grafo[origem].emplace_back(destino);
        
    }  
        // Exibe a lista de adjacência
    std::cout << "\nLista de adjacência:\n";
    for (const auto& [vertex, neighbors] : Grafo) {
        std::cout << "Vértice " << vertex << ":";
        for (const auto& neighbor : neighbors) {
            std::cout << " " << neighbor;
        }
        std::cout << std::endl;
    }

    return 0;
}