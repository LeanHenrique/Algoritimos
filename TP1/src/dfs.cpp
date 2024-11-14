#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/dfs.h"

// Função DFS para preencher a pilha com a ordem de finalização dos vértices
void DfsOrder(const std::string& vertice, 
              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
              std::unordered_set<std::string>& visitados, 
              std::stack<std::string>& pilha) {
    // Marca o vértice como visitado
    visitados.insert(vertice);

    // Percorre todos os vizinhos do vértice
    for (const auto& vizinho : Grafo.at(vertice)) {
        // Realiza a DFS recursiva se o vizinho ainda não foi visitado
        if (visitados.find(vizinho) == visitados.end()) {
            DfsOrder(vizinho, Grafo, visitados, pilha);
        }
    }

    // Ao finalizar a exploração de todos os vizinhos, empilha o vértice
    pilha.push(vertice);
}

// Função DFS para o grafo transposto, usada para marcar um componente fortemente conexo
void DfsTranspose(const std::string& vertice, 
                  const std::unordered_map<std::string, std::vector<std::string>>& GrafoTransposto, 
                  std::unordered_set<std::string>& visitados, 
                  std::vector<std::string>& componente) {
    // Marca o vértice como visitado
    visitados.insert(vertice);

    // Adiciona o vértice ao componente atual
    componente.push_back(vertice);

    // Percorre os vizinhos do vértice no grafo transposto
    for (const auto& vizinho : GrafoTransposto.at(vertice)) {
        // Realiza a DFS recursiva se o vizinho ainda não foi visitado
        if (visitados.find(vizinho) == visitados.end()) {
            DfsTranspose(vizinho, GrafoTransposto, visitados, componente);
        }
    }
}
