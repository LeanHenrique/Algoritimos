#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP2/include/bfs.h"

void bfs(const std::unordered_map<int, std::vector<std::pair<int, int>>>& Graph, int start) {
    std::queue<int> q; // Fila para BFS
    std::set<int> visited; // Conjunto para armazenar os nós visitados

    // Começa a partir do nó inicial
    q.push(start);
    visited.insert(start);

    std::cout << "Ordem de visita BFS a partir do nó " << start << ": ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        std::cout << node << " "; // Processa o nó atual

        // Percorre todos os vizinhos do nó atual
        for (const auto& [neighbor, capacity] : Graph.at(node)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor); // Marca como visitado
                q.push(neighbor); // Adiciona na fila
            }
        }
    }
    std::cout << "\n";
}