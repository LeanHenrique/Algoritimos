#include "dfs.h"

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

// Função DFS adaptada para buscar um ciclo patrulhado no grafo
bool DfsPatrulhamento(
    const std::string& atual, 
    const std::string& origem, 
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>& subgrafo, 
    std::vector<std::string>& ciclo
) {
    // Caso especial: se o grafo tem apenas um vértice e nenhuma aresta, não há patrulhamento possível
    if (subgrafo.size() == 1 && subgrafo.begin()->second.empty()) {
        return false;
    }

    // Visita o vértice atual e o adiciona ao ciclo
    ciclo.push_back(atual);

    // Percorre todas as arestas conectadas ao vértice atual
    auto it = subgrafo.find(atual);
    if (it != subgrafo.end()) {
        std::vector<std::pair<std::string, int>>& vizinhos = it->second;  // Obtém os vizinhos

        // Verifica se todos os pesos das arestas são 0
        bool todasArestasVisitadas = true;
        for (auto& [vertice, vizinhos] : subgrafo) {
            for (auto& [vizinho, peso] : vizinhos) {
                if (peso == 0) {  // Se algum peso for 0, significa que a aresta não foi visitada
                    todasArestasVisitadas = false;
                    break;
                }
            }
            if (!todasArestasVisitadas) break;
        }

        // Se todos os pesos são 0 e o vértice atual for igual ao início, encontrou um ciclo
        if (todasArestasVisitadas && atual == origem) {
            return true;  // Encontrou o ciclo
        }

        // Ordena as arestas por peso
        for (size_t i = 0; i < vizinhos.size(); ++i) {
            for (size_t j = i + 1; j < vizinhos.size(); ++j) {
                if (vizinhos[i].second > vizinhos[j].second) {
                    std::swap(vizinhos[i], vizinhos[j]);  // Troca para garantir a ordem de menor para maior peso
                }
            }
        }

        // Percorre os vizinhos agora ordenados pelo peso
        for (size_t i = 0; i < vizinhos.size(); ++i) {
            // Incrementa o peso da aresta (segundo elemento do par)
            vizinhos[i].second++;

            // Chama recursivamente o DFS para o próximo vizinho
            if (DfsPatrulhamento(vizinhos[i].first, origem, subgrafo, ciclo)) {
                return true;  // Encontrou um ciclo, retorna imediatamente
            }
        }
    }

    // Remove o vértice ao retroceder no DFS
    ciclo.pop_back();
    return false;
}
