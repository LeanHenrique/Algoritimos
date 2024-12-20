#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H

#include <map>
#include <queue>
#include <tuple>

// Definição de valor infinito para representar capacidades muito grandes
#define INFINITO 1000000

// Função BFS para encontrar o caminho aumentante no grafo residual
bool bfs(const std::map<int, std::map<int, int>>& residualGraph, int fonte, int sumidouro, std::map<int, int>& pai);

// Função do algoritmo de Ford-Fulkerson
int fordFulkerson(std::map<int, std::map<int, int>>& capacidade, int fonte, int sumidouro,
                  std::map<int, std::map<int, int>>& arestasMax, const std::map<int, std::map<int, int>>& Graph);

#endif // FORD_FULKERSON_H
