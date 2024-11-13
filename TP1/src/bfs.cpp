#include "/home/lean/Documentos/Algoritmos/Algoritimos/TP1/include/bfs.h"

std::pair<std::string, int> BfsCapital(const std::string& inicio, const std::unordered_map<std::string, std::vector<std::string>>& Grafo) {
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