#include <iostream>
#include <vector>
#include <unordered_map> 


int main() {
    // Grafo representado como mapa de adjacências
    std::unordered_map<int, std::vector<std::pair<int, int>>> Graph;
    std::unordered_map<int, int> nodes; // Armazena tipo (gerador ou consumidor)

    int V, E;
    std::cin >> V >> E;

    // Lendo os pontos da rede
    for (int i = 0; i < V; i++) {
        int indice, demanda;
        std::cin >> indice >> demanda;
        nodes[indice] = demanda;
        Graph[indice] = {}; // Inicializa o grafo com o nó
    }

    // Lendo as conexões da rede
    for (int i = 0; i < E; i++) {
        int Vi, Vj, C;
        std::cin >> Vi >> Vj >> C;
        Graph[Vi].emplace_back(Vj, C); // Adiciona aresta Vi -> Vj com capacidade C
    }

    return 0;
}