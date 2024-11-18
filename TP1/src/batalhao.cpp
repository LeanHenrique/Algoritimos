#include "batalhao.h"
#include "bfs.h"
#include "dfs.h"
#include "auxiliares.h"

// Função principal para encontrar componentes fortemente conexos usando o algoritmo de Kosaraju
int Kosaraju(const std::unordered_map<std::string, std::vector<std::string>>& Grafo, std::vector<std::vector<std::string>>& componentes ) {
    std::unordered_set<std::string> visitados;
    std::stack<std::string> pilha;

    // Passo 1: Realizar DFS no grafo original e preencher a pilha com a ordem de finalização
    for (const auto& [vertice, _] : Grafo) {
        if (visitados.find(vertice) == visitados.end()) {
            DfsOrder(vertice, Grafo, visitados, pilha);  // DFS para determinar a ordem de finalização dos vértices
        }
    }

    // Passo 2: Construir o grafo transposto (invertendo as arestas)
    std::unordered_map<std::string, std::vector<std::string>> GrafoTransposto;
    std::vector<std::string> PossiveisNovasOrigensT;
    for (const auto& [origem, destinos] : Grafo) {
        for (const auto& destino : destinos) {
            GrafoTransposto[destino].emplace_back(origem); // Inverte a direção da aresta
            PossiveisNovasOrigensT.push_back(origem);  // Armazena as origens das arestas
        }
    }

    // Garante que todos os vértices, incluindo destinos, existam no grafo transposto
    for (const auto& vertice : PossiveisNovasOrigensT) {
        if (GrafoTransposto.find(vertice) == GrafoTransposto.end()) {
            GrafoTransposto[vertice] = {};  // Adiciona o vértice com uma lista vazia de vizinhos
        }
    }

    // Passo 3: Realizar DFS no grafo transposto usando a ordem da pilha
    visitados.clear();
    int qtd_batalhões = 0;  // Contador para os batalhões (componentes fortemente conexos)
    while (!pilha.empty()) {
        std::string vertice = pilha.top();  // Pega o vértice do topo da pilha
        pilha.pop();

        // Processa apenas vértices ainda não visitados
        if (visitados.find(vertice) == visitados.end()) {
            std::vector<std::string> componente;  // Cria um novo componente fortemente conexo
            DfsTranspose(vertice, GrafoTransposto, visitados, componente);  // Realiza DFS no grafo transposto
            componentes.push_back(componente);  // Adiciona o componente à lista de componentes
            qtd_batalhões++;  // Incrementa o contador de componentes (batalhões)
        }
    }

    return qtd_batalhões;  // Retorna o número total de batalhões encontrados
}


std::string Batalhaoadicional(const std::string& inicio, 
                              const std::unordered_map<std::string, std::vector<std::string>>& Grafo,
                              const std::vector<std::string>& componente) {
    // Obtém as distâncias de cada vértice a partir do vértice de início usando BFS
    std::unordered_map<std::string, int> distancias = BfsBatalhao(inicio, Grafo);

    // Inicializa o vértice com menor distância e sua distância usando o primeiro vértice válido
    std::string vertice_min_distancia;
    int menor_distancia = 100000;  // Valor alto para garantir que qualquer distância válida será menor
    bool encontrado = false;  // Flag para indicar se algum vértice válido foi encontrado

    // Lista para armazenar os vértices empatados (com a mesma distância)
    std::vector<std::string> vertices_empate;

    // Percorre os vértices no componente para encontrar os que têm a menor distância
    for (const std::string& vertice : componente) {
        // Verifica se o vértice está nas distâncias calculadas
        if (distancias.find(vertice) != distancias.end()) {
            int distancia_atual = distancias[vertice];

            // Se for a primeira distância válida ou menor que a distância atual, atualize
            if (!encontrado || distancia_atual < menor_distancia) {
                menor_distancia = distancia_atual;  // Atualiza a menor distância
                vertice_min_distancia = vertice;    // Atualiza o vértice com a menor distância
                vertices_empate.clear();  // Limpa os vértices anteriores
                vertices_empate.push_back(vertice);  // Armazena o novo vértice com a menor distância
                encontrado = true;  // Marca que encontramos pelo menos um vértice válido
            }
            // Caso encontre outro vértice com a mesma distância
            else if (distancia_atual == menor_distancia) {
                vertices_empate.push_back(vertice);  // Adiciona o vértice empatado
            }
        }
    }

    // Se houver mais de um vértice empatado, resolve o desempate
    if (vertices_empate.size() > 1) {
        // Cria o subgrafo para o componente
        std::unordered_map<std::string, std::vector<std::string>> subgrafo = criaSubgrafoBatalhao(Grafo, componente);

        // Armazena o vértice com a menor distância (por critério de desempate)
        std::string vertice_desempate;
        int menor_distancia_subgrafo = 100000;  // Valor alto para garantir que qualquer distância válida será menor

        // Compara os vértices empatados no subgrafo
        for (const auto& vertice_empate : vertices_empate) {
            // Obtém as distâncias dentro do subgrafo
            std::unordered_map<std::string, int> distancias_subgrafo = BfsBatalhao(vertice_empate, subgrafo);

            // Calcula a distância total para os outros vértices dentro do subgrafo
            int distancia_total = 0;
            for (const auto& vertice : componente) {
                if (distancias_subgrafo.find(vertice) != distancias_subgrafo.end()) {
                    distancia_total += distancias_subgrafo[vertice];  // Soma as distâncias dos outros vértices
                }
            }

            // Atualiza o vértice desempate se encontrar uma distância total menor
            if (distancia_total < menor_distancia_subgrafo) {
                menor_distancia_subgrafo = distancia_total;
                vertice_desempate = vertice_empate;
            }
        }

        // Retorna o vértice com a menor distância total dentro do subgrafo
        return vertice_desempate;
    }

    // Caso não haja empate, retorna o vértice com a menor distância
    return vertice_min_distancia;
}