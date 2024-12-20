#include "ford_fulkerson.h"
#include <queue>

// Função BFS para encontrar o caminho aumentante
// A função retorna true se um caminho aumentante foi encontrado do 'fonte' ao 'sumidouro'
bool bfs(const std::map<int, std::map<int, int>>& residualGraph, int fonte, int sumidouro, std::map<int, int>& pai) {
    std::map<int, bool> visitado;  // Mapa para verificar se um nó já foi visitado
    std::queue<int> fila;  // Fila para armazenar os nós a serem visitados

    fila.push(fonte);  // Começa a busca a partir da fonte
    visitado[fonte] = true;  // Marca a fonte como visitada
    pai[fonte] = -1;  // Não há pai para a fonte

    // Enquanto houver nós na fila, realiza a busca
    while (!fila.empty()) {
        int u = fila.front();  // Pega o primeiro nó da fila
        fila.pop();  // Remove o nó da fila

        // Percorre todos os vizinhos de 'u'
        for (const auto& [v, cap] : residualGraph.at(u)) {
            // Se o nó 'v' não foi visitado e há capacidade residual
            if (!visitado[v] && cap > 0) {
                fila.push(v);  // Adiciona 'v' à fila
                pai[v] = u;  // Registra o pai de 'v'
                visitado[v] = true;  // Marca 'v' como visitado

                // Se chegamos ao sumidouro, retornamos true
                if (v == sumidouro) return true;
            }
        }
    }

    return false;  // Retorna false se não houver caminho aumentante
}

// Implementação do algoritmo de Ford-Fulkerson
int fordFulkerson(std::map<int, std::map<int, int>>& capacidade, int fonte, int sumidouro,
                  std::map<int, std::map<int, int>>& arestasMax, const std::map<int, std::map<int, int>>& Graph) {
    // Copia o grafo de capacidades para o grafo residual
    std::map<int, std::map<int, int>> residualGraph = capacidade;
    std::map<int, int> pai;  // Mapa para armazenar os pais dos nós no caminho aumentante
    int fluxoMaximo = 0;  // Variável para armazenar o fluxo máximo

    // Enquanto existir um caminho aumentante
    while (bfs(residualGraph, fonte, sumidouro, pai)) {
        int fluxoCaminho = INFINITO;  // Fluxo que pode ser enviado pelo caminho encontrado

        // Calcula o fluxo máximo possível no caminho aumentante encontrado
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            fluxoCaminho = std::min(fluxoCaminho, residualGraph[u][v]);  // Fluxo é o mínimo da capacidade residual
        }

        // Atualiza o grafo residual após enviar o fluxo
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            residualGraph[u][v] -= fluxoCaminho;  // Subtrai o fluxo na aresta u -> v
            residualGraph[v][u] += fluxoCaminho;  // Adiciona o fluxo na aresta reversa v -> u

            // Se a aresta u -> v atingiu sua capacidade máxima, salva no mapa de arestasMax
            if (residualGraph[u][v] == 0 && Graph.count(u) && Graph.at(u).count(v) && capacidade[u][v] > 0) {
                // Verifica se a aresta (u, v) está no grafo original e se atingiu sua capacidade máxima
                arestasMax[u][v] = capacidade[u][v];
            }
        }

        // Adiciona o fluxo do caminho aumentante ao fluxo máximo
        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo;  // Retorna o fluxo máximo calculado
}
