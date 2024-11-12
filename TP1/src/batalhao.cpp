#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/batalhao.h"

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

std::unordered_map<std::string, int> BfsBatalhao(const std::string& inicio, const std::unordered_map<std::string, std::vector<std::string>>& Grafo) {
    // Um mapa para armazenar se o vértice foi visitado
    std::unordered_map<std::string, bool> visitados;

    // Mapa para armazenar a distância de cada vértice ao vértice de início
    std::unordered_map<std::string, int> distancias;
    
    // Fila para o BFS
    std::queue<std::string> q;
    
    // Inicializa a distância do início como 0
    distancias[inicio] = 0;
    visitados[inicio] = true;
    q.push(inicio);

    // Enquanto houver vértices na fila
    while (!q.empty()) {
        // Pega o vértice da frente da fila
        std::string v = q.front();
        q.pop();

        // Visita os vizinhos do vértice atual
        for (const std::string& vizinho : Grafo.at(v)) {
            if (visitados.find(vizinho) == visitados.end()) {  // Se o vizinho ainda não foi visitado
                visitados[vizinho] = true;  // Marca o vizinho como visitado
                distancias[vizinho] = distancias[v] + 1;  // Atualiza a distância do vizinho
                q.push(vizinho);  // Coloca o vizinho na fila
            }
        }
    }

return distancias;
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