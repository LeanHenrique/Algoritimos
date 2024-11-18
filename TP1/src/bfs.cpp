#include "bfs.h"

// Função BFS para encontrar o vértice mais distante a partir do vértice inicial (Capital)
std::pair<std::string, int> BfsCapital(const std::string& inicio, 
                                       const std::unordered_map<std::string, std::vector<std::string>>& Grafo) {
    // Mapa para armazenar se o vértice foi visitado
    std::unordered_map<std::string, bool> visitados;

    // Mapa para armazenar a distância de cada vértice ao vértice de início
    std::unordered_map<std::string, int> distancias;

    // Fila para o BFS (Armazena os vértices a serem visitados)
    std::queue<std::string> q;

    // Inicializa a distância do vértice de início como 0 e o marca como visitado
    distancias[inicio] = 0;
    visitados[inicio] = true;
    q.push(inicio);

    // Realiza o BFS enquanto houver vértices na fila
    while (!q.empty()) {
        std::string v = q.front();  // Pega o vértice da frente da fila
        q.pop();  // Remove o vértice da fila

        // Visita os vizinhos do vértice atual
        for (const std::string& vizinho : Grafo.at(v)) {
            if (visitados.find(vizinho) == visitados.end()) {  // Se o vizinho ainda não foi visitado
                visitados[vizinho] = true;  // Marca o vizinho como visitado
                distancias[vizinho] = distancias[v] + 1;  // Atualiza a distância do vizinho
                q.push(vizinho);  // Coloca o vizinho na fila
            }
        }
    }

    // Verifica se o grafo é conexo a partir do vértice de início
    if (visitados.size() != Grafo.size()) {
        // Se o grafo não for conexo, retorna um par vazio
        return {"", -1};
    }

    // Encontra o vértice com a maior distância
    int maiorDistanciaValor = -1;  // Inicializa com um valor menor que qualquer distância válida
    std::string verticeMaisDistante;

    for (const auto& par : distancias) {
        if (par.second > maiorDistanciaValor) {
            maiorDistanciaValor = par.second;  // Atualiza a maior distância
            verticeMaisDistante = par.first;  // Atualiza o vértice com a maior distância
        }
    }

    // Retorna o vértice mais distante e a sua distância
    return {verticeMaisDistante, maiorDistanciaValor};
}

// Função BFS para calcular as distâncias de cada vértice a partir do vértice inicial (Batalhão)
std::unordered_map<std::string, int> BfsBatalhao(const std::string& inicio, 
                                                const std::unordered_map<std::string, std::vector<std::string>>& Grafo) {
    // Mapa para armazenar se o vértice foi visitado
    std::unordered_map<std::string, bool> visitados;

    // Mapa para armazenar a distância de cada vértice ao vértice de início
    std::unordered_map<std::string, int> distancias;

    // Fila para o BFS (Armazena os vértices a serem visitados)
    std::queue<std::string> q;

    // Inicializa a distância do vértice de início como 0 e o marca como visitado
    distancias[inicio] = 0;
    visitados[inicio] = true;
    q.push(inicio);

    // Realiza o BFS enquanto houver vértices na fila
    while (!q.empty()) {
        std::string v = q.front();  // Pega o vértice da frente da fila
        q.pop();  // Remove o vértice da fila

        // Visita os vizinhos do vértice atual
        for (const std::string& vizinho : Grafo.at(v)) {
            if (visitados.find(vizinho) == visitados.end()) {  // Se o vizinho ainda não foi visitado
                visitados[vizinho] = true;  // Marca o vizinho como visitado
                distancias[vizinho] = distancias[v] + 1;  // Atualiza a distância do vizinho
                q.push(vizinho);  // Coloca o vizinho na fila
            }
        }
    }

    // Retorna o mapa com as distâncias calculadas de todos os vértices
    return distancias;
}

