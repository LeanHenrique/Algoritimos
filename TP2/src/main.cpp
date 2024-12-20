#include <iostream>
#include <unordered_map>
#include <queue>
#include <climits> // Para usar INT_MAX

#define INFINITO INT_MAX

bool bfs(const std::unordered_map<int, std::unordered_map<int, int>>& residualGraph, int fonte, int sumidouro, std::unordered_map<int, int>& pai) {
    std::unordered_map<int, bool> visitado;
    std::queue<int> fila;

    fila.push(fonte);
    visitado[fonte] = true;
    pai[fonte] = -1;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        // Percorre todos os nós vizinhos de `u`
        for (const auto& [v, cap] : residualGraph.at(u)) {
            if (!visitado[v] && cap > 0) { // Se há capacidade residual
                fila.push(v);
                pai[v] = u;
                visitado[v] = true;

                if (v == sumidouro) return true; // Se chegamos ao sumidouro
            }
        }
    }

    return false; // Não há caminho aumentante
}

int fordFulkerson(std::unordered_map<int, std::unordered_map<int, int>>& capacidade, int fonte, int sumidouro) {
    std::unordered_map<int, std::unordered_map<int, int>> residualGraph = capacidade;
    std::unordered_map<int, int> pai;
    int fluxoMaximo = 0;

    while (bfs(residualGraph, fonte, sumidouro, pai)) {
        int fluxoCaminho = INFINITO;

        // Calcula o fluxo máximo possível no caminho aumentante encontrado
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            fluxoCaminho = std::min(fluxoCaminho, residualGraph[u][v]);
        }

        // Atualiza o grafo residual
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            residualGraph[u][v] -= fluxoCaminho;
            residualGraph[v][u] += fluxoCaminho;
        }

        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo;
}

int main() {
    std::unordered_map<int, std::unordered_map<int, int>> Graph;
    std::unordered_map<int, int> nodes;

    int V, E;
    std::cin >> V >> E;

    // Lendo os nós e suas demandas
    for (int i = 0; i < V; i++) {
        int indice, demanda;
        std::cin >> indice >> demanda;
        nodes[indice] = demanda;
    }

    // Lendo as conexões da rede
    for (int i = 0; i < E; i++) {
        int Vi, Vj, C;
        std::cin >> Vi >> Vj >> C;
        Graph[Vi][Vj] = C; // Adiciona a capacidade da aresta Vi -> Vj
    }

    // Construção do grafo com fonte e sumidouro artificiais
    int fonteArtificial = 0;
    int sumidouroArtificial = V + 1;

    // Criação do grafo de capacidades
    std::unordered_map<int, std::unordered_map<int, int>> capacidade;

    // Adiciona as capacidades do grafo original
    for (const auto& [u, arestas] : Graph) {
        for (const auto& [v, cap] : arestas) {
            capacidade[u][v] = cap;
        }
    }

    // Conecta a fonte artificial aos geradores
    for (const auto& [nodo, tipo] : nodes) {
        if (tipo == 0) { // Gerador
            capacidade[fonteArtificial][nodo] = INFINITO;
        }
    }

    // Conecta os consumidores ao sumidouro artificial
    for (const auto& [nodo, tipo] : nodes) {
        if (tipo > 0) { // Consumidor com demanda
            capacidade[nodo][sumidouroArtificial] = tipo;
        }
    }

    // Executa o algoritmo de Ford-Fulkerson
    int fluxoMaximo = fordFulkerson(capacidade, fonteArtificial, sumidouroArtificial);

    // Exibe o fluxo máximo total
    std::cout << "Fluxo máximo total: " << fluxoMaximo << "\n";

    return 0;
}
