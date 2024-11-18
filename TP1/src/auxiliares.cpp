#include "auxiliares.h"

// Função para criar subgrafos a partir dos componentes
std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> criaSubgrafos(
    const std::unordered_map<std::string, std::vector<std::string>>& grafo,
    const std::vector<std::vector<std::string>>& componentes) {
    
    // Lista para armazenar cada subgrafo (um por componente)
    std::vector<std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>> subgrafos;

    // Itera sobre cada componente
    for (const auto& componente : componentes) {
        // Cria um subgrafo para o componente atual
        std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> subgrafo = criaSubgrafo(grafo, componente);
        
        // Adiciona o subgrafo à lista de subgrafos
        subgrafos.push_back(subgrafo);
    }
    
    return subgrafos;
}

// Função para criar um subgrafo a partir de um componente específico
std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> 
criaSubgrafo(const std::unordered_map<std::string, std::vector<std::string>>& grafo,
             const std::vector<std::string>& componente) {

    // Inicializa o subgrafo para este componente
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> subgrafo;

    // Conjunto para verificar rapidamente se um vértice pertence à região (componente)
    std::unordered_set<std::string> regiaoSet(componente.begin(), componente.end());

    // Adiciona as arestas entre os vértices da região
    for (const auto& vertice : componente) {
        bool verticeTemArestas = false;  // Flag para verificar se o vértice tem arestas na região
        for (const auto& vizinho : grafo.at(vertice)) {
            // Verifica se o vizinho pertence à região (componente)
            if (regiaoSet.find(vizinho) != regiaoSet.end()) {
                // Adiciona a aresta com peso 0 (não estamos utilizando peso aqui, então é 0)
                subgrafo[vertice].push_back({vizinho, 0});  
                verticeTemArestas = true;
            }
        }

        // Se o vértice não tiver arestas, ainda assim é adicionado ao subgrafo
        if (!verticeTemArestas) {
            subgrafo[vertice] = {};  // Adiciona o vértice com uma lista vazia de vizinhos
        }
    }
    return subgrafo;
}

// Função para criar um subgrafo (com arestas simples, sem pesos) para o componente
std::unordered_map<std::string, std::vector<std::string>> 
criaSubgrafoBatalhao(const std::unordered_map<std::string, std::vector<std::string>>& grafo,
                     const std::vector<std::string>& componente) {
    
    // Inicializa o subgrafo para este componente
    std::unordered_map<std::string, std::vector<std::string>> subgrafo;

    // Conjunto para verificar rapidamente se um vértice pertence à região (componente)
    std::unordered_set<std::string> regiaoSet(componente.begin(), componente.end());

    // Adiciona as arestas entre os vértices da região
    for (const auto& vertice : componente) {
        bool verticeTemArestas = false;  // Flag para verificar se o vértice tem arestas na região
        for (const auto& vizinho : grafo.at(vertice)) {
            // Verifica se o vizinho pertence à região (componente)
            if (regiaoSet.find(vizinho) != regiaoSet.end()) {
                // Adiciona o vizinho ao subgrafo sem peso (apenas o nome do vizinho)
                subgrafo[vertice].push_back(vizinho);  
                verticeTemArestas = true;
            }
        }

        // Se o vértice não tiver arestas, ainda assim é adicionado ao subgrafo
        if (!verticeTemArestas) {
            subgrafo[vertice] = {};  // Adiciona o vértice com uma lista vazia de vizinhos
        }
    }
    return subgrafo;
}
