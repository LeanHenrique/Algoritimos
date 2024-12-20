#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

#define INFINITO 1000000 // Substitui INT_MAX por um valor grande

// Função BFS para encontrar o caminho aumentante
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

// Função para verificar se um valor está em um vetor
bool find(const std::vector<int>& vec, int valor) {
    // Percorre o vetor e compara cada elemento com o valor
    for (std::size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == valor) {
            return true; // Retorna o índice se o valor for encontrado
        }
    }
    return false; // Retorna false se o valor não for encontrado
}

// Implementação do algoritmo de Ford-Fulkerson
int fordFulkerson(std::unordered_map<int, std::unordered_map<int, int>>& capacidade, int fonte, int sumidouro, 
                  std::unordered_map<int, std::unordered_map<int, int>>& arestasMax, const std::unordered_map<int, std::unordered_map<int, int>>& Graph) {
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

    // Verifica as arestas com capacidade máxima atingida após o algoritmo
    for (const auto& [u, arestas] : capacidade) {
        for (const auto& [v, cap] : arestas) {
            // Verifica se a aresta existe no grafo original
            if (residualGraph[u][v] == 0 && cap > 0 && Graph.find(u) != Graph.end() && Graph.at(u).find(v) != Graph.at(u).end()) {
                // Se a aresta existe no grafo original e atingiu a capacidade máxima, adiciona a aresta à lista
                arestasMax[u][v] = cap;
            }
        }
    }

    return fluxoMaximo;
}

void ordenarArestas(std::vector<std::tuple<int, int, int>>& arestas) {
    std::vector<std::tuple<int, int, int>>::size_type n = arestas.size(); // Corrigido
    // Implementação do algoritmo Bubble Sort para ordenar as arestas pela capacidade (decrescente)
    for (std::vector<std::tuple<int, int, int>>::size_type i = 0; i < n - 1; ++i) {
        for (std::vector<std::tuple<int, int, int>>::size_type j = 0; j < n - 1 - i; ++j) {
            if (std::get<2>(arestas[j]) < std::get<2>(arestas[j + 1])) {
                // Troca os elementos se estiverem na ordem errada
                std::swap(arestas[j], arestas[j + 1]);
            }
        }
    }
}


int main() {
    std::unordered_map<int, std::unordered_map<int, int>> Graph;
    std::unordered_map<int, int> nodes;
    std::vector<int> Geradores;
    int DemandaMax = 0;
    int EnergiaMax = 0;

    int V, E;
    std::cin >> V >> E;

    // Lendo os nós e suas demandas
    for (int i = 0; i < V; i++) {
        int indice, demanda;
        std::cin >> indice >> demanda;
        DemandaMax += demanda;
        if(demanda == 0){
            Geradores.push_back(indice);
        }
        nodes[indice] = demanda;
    }

    // Lendo as conexões da rede
    for (int i = 0; i < E; i++) {
        int Vi, Vj, C;
        std::cin >> Vi >> Vj >> C;
        if(find(Geradores,Vi)){
            EnergiaMax += C;
        }
        if(Vi)
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

    // Mapa para armazenar as arestas que atingiram a capacidade máxima
    std::unordered_map<int, std::unordered_map<int, int>> arestasMax;

    // Executa o algoritmo de Ford-Fulkerson
    int fluxoMaximo = fordFulkerson(capacidade, fonteArtificial, sumidouroArtificial, arestasMax, Graph);
    int Energia_perdida = EnergiaMax - fluxoMaximo;
    int Energia_NAtendida =  DemandaMax - fluxoMaximo;

    // Exibe o fluxo máximo total
    std::cout << fluxoMaximo << std::endl;
    std::cout << Energia_NAtendida << std::endl;
    std::cout << Energia_perdida << std::endl;

    // Ordena as arestas com capacidade máxima atingida por capacidade (decrescente)
    std::vector<std::tuple<int, int, int>> arestasOrdenadas;
    for (const auto& [u, arestas] : arestasMax) {
        for (const auto& [v, cap] : arestas) {
            arestasOrdenadas.push_back({u, v, cap});
        }
    }

    // Ordena as arestas pela capacidade (em ordem decrescente)
    ordenarArestas(arestasOrdenadas);

    // Exibe as arestas com capacidade máxima atingida
    std::cout << arestasOrdenadas.size() << std::endl;
    for (const auto& [u, v, cap] : arestasOrdenadas) {
        std::cout << u << " " << v << " " << cap << std::endl;
    }

    return 0;
}
