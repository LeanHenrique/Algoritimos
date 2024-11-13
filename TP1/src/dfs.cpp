#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/dfs.h"

// Função DFS para preencher a pilha com a ordem de finalização dos vértices
void DfsOrder(const std::string& vertice, 
              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
              std::unordered_set<std::string>& visitados, 
              std::stack<std::string>& pilha) {
    visitados.insert(vertice);
    for (const auto& vizinho : Grafo.at(vertice)) {
        if (visitados.find(vizinho) == visitados.end()) {
            DfsOrder(vizinho, Grafo, visitados, pilha);
        }
    }
    pilha.push(vertice); // Armazena o vértice na pilha ao final da exploração
}

// Função DFS para o grafo transposto para marcar um componente fortemente conexo
void DfsTranspose(const std::string& vertice, 
                  const std::unordered_map<std::string, std::vector<std::string>>& GrafoTransposto, 
                  std::unordered_set<std::string>& visitados, std::vector<std::string>& componente) {
    visitados.insert(vertice);
    componente.push_back(vertice);
    for (const auto& vizinho : GrafoTransposto.at(vertice)) {
        if (visitados.find(vizinho) == visitados.end()) {
            DfsTranspose(vizinho, GrafoTransposto, visitados,componente);
        }
    }
}



