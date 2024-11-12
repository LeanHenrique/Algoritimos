#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/capital.h"
#include <queue>
#include <iostream>



std::pair<std::string, int> Bfs(const std::string& inicio, const std::unordered_map<std::string, std::vector<std::string>>& Grafo) {
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

    // Verifica se o grafo é conexo a partir do vértice de início
    if (visitados.size() != Grafo.size()) {
        // Caso o grafo não seja conexo, retorna um par vazio (ou outro valor de erro)
        return {"", -1};
    }

// Encontrar o vértice com a maior distância manualmente
int maiorDistanciaValor = -1; // Ou qualquer valor inicial que seja mais baixo que a distância mínima possível

// Iterar sobre todas as distâncias para encontrar o maior
for (const auto& par : distancias) {
    if (par.second > maiorDistanciaValor) {
        maiorDistanciaValor = par.second;
    }
}
    std::pair<std::string, int> parResultado = {inicio, maiorDistanciaValor};                      

    // Retorna o par (vértice, maior distância)
    return parResultado;
}

std::string Capital(const std::unordered_map<std::string, std::vector<std::string>>& Grafo){
    // Mapa para armazenar os resultados de cada BFS
    std::unordered_map<std::string, std::pair<std::string, int>> resultados;
   for (const auto& [vertice, _] : Grafo) {
        resultados[vertice] = Bfs(vertice, Grafo);
    }
    // Variáveis para armazenar o vértice com a maior distância
    std::string verticeMenorDistancia;
    int menorDistancia = 100000;  // Inicializa com valor negativo para garantir que qualquer distância será maior.

    // Itera sobre os resultados e encontra o vértice com a maior distância
    for (const auto& [vertice, par] : resultados) {
        if (par.second < menorDistancia && par.second >=0) {
            menorDistancia = par.second;
            verticeMenorDistancia = vertice;
        }
    }

    return verticeMenorDistancia;  // Retorna o vértice com a maior distância
}