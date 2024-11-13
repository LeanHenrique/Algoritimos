#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/batalhao.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/bfs.h"
#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/dfs.h"



// Função principal para encontrar componentes fortemente conexos usando o algoritmo de Kosaraju
int Kosaraju(const std::unordered_map<std::string, std::vector<std::string>>& Grafo, std::vector<std::vector<std::string>>& componentes ) {
    std::unordered_set<std::string> visitados;
    std::stack<std::string> pilha;

    // Passo 1: Realizar DFS no grafo original e preencher a pilha com a ordem de finalização
    for (const auto& [vertice, _] : Grafo) {
        if (visitados.find(vertice) == visitados.end()) {
            DfsOrder(vertice, Grafo, visitados, pilha);
        }
    }

    // Passo 2: Construir o grafo transposto (invertendo as arestas)
    std::unordered_map<std::string, std::vector<std::string>> GrafoTransposto;
    std::vector<std::string> PossiveisNovasOrigensT;
    for (const auto& [origem, destinos] : Grafo) {
        for (const auto& destino : destinos) {
            GrafoTransposto[destino].emplace_back(origem); // Inverte a direção da aresta
            PossiveisNovasOrigensT.push_back(origem);
        }
    }
    // Garante que todos os vértices, incluindo destinos, existam no grafo
    for (const auto& vertice : PossiveisNovasOrigensT) {
        if (GrafoTransposto.find(vertice) == GrafoTransposto.end()) {
            GrafoTransposto[vertice] = {}; // Adiciona o vértice com uma lista vazia de vizinhos
        }
    }

    // Passo 3: Realizar DFS no grafo transposto usando a ordem da pilha
    visitados.clear();
    int qtd_batalhões = 0;
    while (!pilha.empty()) {
        std::string vertice = pilha.top();
        pilha.pop();

        // Processa apenas vértices ainda não visitados
        if (visitados.find(vertice) == visitados.end()) {
            std::vector<std::string> componente; // Cria um novo componente
            DfsTranspose(vertice, GrafoTransposto, visitados, componente);
            componentes.push_back(componente); 
            qtd_batalhões++;
            
        }
    }
    return qtd_batalhões;
}


std::string Batalhaoadicional(const std::string& inicio, 
                              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
                              const std::vector<std::string>& componente) {
    // Obtenha as distâncias de cada vértice a partir do vértice de início
    std::unordered_map<std::string, int> distancias = BfsBatalhao(inicio, Grafo);

    // Inicializa o vértice com menor distância e sua distância usando o primeiro vértice válido
    std::string vertice_min_distancia;
    int menor_distancia = 100000;
    bool encontrado = false;

    // Percorre os vértices no componente para encontrar o que tem a menor distância
    for (const std::string& vertice : componente) {
        // Verifica se o vértice está nas distâncias calculadas
        if (distancias.find(vertice) != distancias.end()) {
            int distancia_atual = distancias[vertice];
            
            // Se for a primeira distância válida ou menor que a distância atual, atualize
            if (!encontrado || distancia_atual < menor_distancia) {
                menor_distancia = distancia_atual;
                vertice_min_distancia = vertice;
                encontrado = true; // Marca que encontramos pelo menos um vértice válido
            }
        }
    }

    // Retorna o vértice com a menor distância ou uma string vazia caso não encontre nenhum
    return encontrado ? vertice_min_distancia : "";
}