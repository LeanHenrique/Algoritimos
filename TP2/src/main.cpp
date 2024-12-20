#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits> // Para usar INT_MAX

#define INFINITO INT_MAX

bool bfs(const std::vector<std::vector<int>>& residualGraph, int fonte, int sumidouro, std::vector<int>& pai) {
    std::size_t n = residualGraph.size(); // Tamanho do grafo residual
    std::vector<bool> visitado(n, false); // Vetor para marcar os nós já visitados
    std::queue<int> fila;

    fila.push(fonte); // Começamos da fonte artificial
    visitado[fonte] = true;
    pai[fonte] = -1; // A fonte não tem "pai"

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        // Percorre todos os nós vizinhos de `u`
        for (std::size_t v = 0; v < n; ++v) { // Usa std::size_t para iterar no vetor
            if (!visitado[v] && residualGraph[u][v] > 0) { // Verifica capacidade residual
                fila.push(static_cast<int>(v)); // Casting explícito para int
                pai[v] = u; // Marca `u` como o pai de `v`
                visitado[v] = true;

                if (v == static_cast<std::size_t>(sumidouro)) return true; // Se chegamos ao sumidouro, paramos
            }
        }
    }

    return false; // Não há caminho aumentante
}


// Implementação do algoritmo de Ford-Fulkerson
int fordFulkerson(std::vector<std::vector<int>>& capacidade, int fonte, int sumidouro) {
    std::size_t n = capacidade.size(); // Corrigido: std::size_t é o tipo adequado para tamanhos de contêineres
    std::vector<std::vector<int>> residualGraph = capacidade; // Grafo residual inicializado com as capacidades originais
    std::vector<int> pai(n); // Vetor para armazenar o caminho encontrado

    int fluxoMaximo = 0; // Variável para armazenar o fluxo máximo

    // Enquanto conseguimos encontrar um caminho aumentante
    while (bfs(residualGraph, fonte, sumidouro, pai)) {
        int fluxoCaminho = INFINITO;

        // Calcula o fluxo máximo possível no caminho aumentante encontrado
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            fluxoCaminho = std::min(fluxoCaminho, residualGraph[u][v]);
        }

        // Atualiza o grafo residual reduzindo a capacidade no caminho direto
        // e aumentando a capacidade no caminho reverso
        for (int v = sumidouro; v != fonte; v = pai[v]) {
            int u = pai[v];
            residualGraph[u][v] -= fluxoCaminho;
            residualGraph[v][u] += fluxoCaminho;
        }

        // Incrementa o fluxo máximo com o fluxo do caminho atual
        fluxoMaximo += fluxoCaminho;
    }

    return fluxoMaximo; // Retorna o fluxo máximo encontrado
}

int main() {
    // Grafo representado como mapa de adjacências
    std::unordered_map<int, std::vector<std::pair<int, int>>> Graph;
    std::unordered_map<int, int> nodes; // Armazena tipo (gerador ou consumidor)

    int V, E;
    std::cin >> V >> E;

    // Lendo os pontos da rede
    for (int i = 0; i < V; i++) {
        int indice, demanda;
        std::cin >> indice >> demanda;
        nodes[indice] = demanda;
        Graph[indice] = {}; // Inicializa o grafo com o nó
    }

    // Lendo as conexões da rede
    for (int i = 0; i < E; i++) {
        int Vi, Vj, C;
        std::cin >> Vi >> Vj >> C;
        Graph[Vi].emplace_back(Vj, C); // Adiciona aresta Vi -> Vj com capacidade C
    }

    // Construção do grafo com fonte e sumidouro artificiais
    int fonteArtificial = 0;
    int sumidouroArtificial = V + 1;

    // Criação do grafo de capacidades
    std::vector<std::vector<int>> capacidade(V + 2, std::vector<int>(V + 2, 0));

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
