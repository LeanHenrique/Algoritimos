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


// Função para determinar o vértice com a menor distância em um componente, a partir de um vértice inicial
std::string Batalhaoadicional(const std::string& inicio, 
                              const std::unordered_map<std::string, std::vector<std::string>>& Grafo, 
                              const std::vector<std::string>& componente) {
    // Obtém as distâncias de cada vértice a partir do vértice de início usando BFS
    std::unordered_map<std::string, int> distancias = BfsBatalhao(inicio, Grafo);

    // Inicializa o vértice com menor distância e sua distância usando o primeiro vértice válido
    std::string vertice_min_distancia;
    int menor_distancia = 100000;  // Valor alto para garantir que qualquer distância válida será menor
    bool encontrado = false;  // Flag para indicar se algum vértice válido foi encontrado

    // Percorre os vértices no componente para encontrar o que tem a menor distância
    for (const std::string& vertice : componente) {
        // Verifica se o vértice está nas distâncias calculadas
        if (distancias.find(vertice) != distancias.end()) {
            int distancia_atual = distancias[vertice];

            // Se for a primeira distância válida ou menor que a distância atual, atualize
            if (!encontrado || distancia_atual < menor_distancia) {
                menor_distancia = distancia_atual;  // Atualiza a menor distância
                vertice_min_distancia = vertice;    // Atualiza o vértice com a menor distância
                encontrado = true;  // Marca que encontramos pelo menos um vértice válido
            }
        }
    }

    // Retorna o vértice com a menor distância ou uma string vazia caso não encontre nenhum
    return encontrado ? vertice_min_distancia : "";  // Retorna o vértice com a menor distância ou vazio
}