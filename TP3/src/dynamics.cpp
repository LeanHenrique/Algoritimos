#include <iostream>
#include "dynamics.h"

using namespace std;

const int INF = 1e9; // Substituindo INT_MAX por um valor grande pré-definido

pair<int, vector<string>> tspDynamicProgramming(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& adjMatrix) {
    size_t n = cities.size();  // Usar size_t em vez de int
    int allVisited = (1 << n) - 1; // Representação binária de todas as cidades visitadas
    unordered_map<string, size_t> cityIndex; // Mapeia o nome da cidade para o índice (usar size_t)
    for (size_t i = 0; i < n; i++) {  // Usar size_t no loop
        cityIndex[cities[i]] = i;
    }

    // dp[mask][i] representa o custo mínimo de percorrer o conjunto de cidades 'mask' e terminar na cidade 'i'
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<size_t>> parent(1 << n, vector<size_t>(n, static_cast<size_t>(-1))); // Para reconstrução da rota, usar size_t

    // Começamos com a cidade 0
    dp[1][0] = 0;

    // Preenche a tabela dp
    for (int mask = 1; mask < (1 << n); mask++) {
        for (size_t u = 0; u < n; u++) {  // Usar size_t no loop
            if (dp[mask][u] == INF) continue;
            for (size_t v = 0; v < n; v++) {  // Usar size_t no loop
                if ((mask & (1 << v)) == 0) { // Se a cidade v ainda não foi visitada
                    int newMask = mask | (1 << v);
                    int newCost = dp[mask][u] + adjMatrix.at(cities[u]).at(cities[v]);
                    if (newCost < dp[newMask][v]) {
                        dp[newMask][v] = newCost;
                        parent[newMask][v] = u;
                    }
                }
            }
        }
    }

    // Encontrar o custo mínimo e reconstruir a melhor rota
    int minCost = INF;
    size_t lastCity = static_cast<size_t>(-1); // Usar size_t para lastCity
    for (size_t i = 1; i < n; i++) {  // Usar size_t no loop
        int cost = dp[allVisited][i] + adjMatrix.at(cities[i]).at(cities[0]);
        if (cost < minCost) {
            minCost = cost;
            lastCity = i;
        }
    }

    // Reconstruir a rota
    vector<string> bestRoute;
    size_t mask = allVisited;
    while (lastCity != static_cast<size_t>(-1)) {  // Usar size_t para lastCity
        bestRoute.push_back(cities[lastCity]);
        size_t temp = lastCity;
        lastCity = parent[mask][lastCity];
        mask ^= (1 << temp);
    }

    // Inversão manual da rota
    vector<string> reversedRoute;
    for (size_t i = bestRoute.size() - 1; i > 0; --i) {  // Usar size_t no loop e i > 0
        reversedRoute.push_back(bestRoute[i]);
    }
    reversedRoute.push_back(bestRoute[0]); // Adiciona a cidade inicial

    return {minCost, reversedRoute}; // Retorna o menor custo e a melhor rota
}
