#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "heuristic.h"

using namespace std;

// Função para o algoritmo Nearest Neighbor
pair<int, vector<string>> tspNearestNeighbor(const vector<string>& cities, const unordered_map<string, unordered_map<string, int>>& adjMatrix) {
    size_t n = cities.size();  // Usar size_t para garantir compatibilidade com índices de vetores
    unordered_map<string, size_t> cityIndex;  // Mapeia o nome da cidade para o índice

    for (size_t i = 0; i < n; i++) {
        cityIndex[cities[i]] = i;
    }

    vector<bool> visited(n, false);  // Marca as cidades já visitadas
    vector<string> route;           // Armazena a sequência das cidades visitadas
    int totalCost = 0;              // Custo total da rota
    const int INF = 1000000;        // Definindo um valor suficientemente grande para representar "infinito"

    // Começamos com a primeira cidade
    route.push_back(cities[0]);
    visited[0] = true;
    size_t currentCity = 0;         // Usar size_t para armazenar o índice da cidade atual

    // Visitar todas as cidades
    for (size_t i = 1; i < n; i++) {
        size_t nearestCity = -1;   // Usar size_t aqui para garantir que o tipo é compatível
        int minDistance = INF;

        // Encontra a cidade mais próxima
        for (size_t j = 0; j < n; j++) {
            if (!visited[j] && adjMatrix.at(cities[currentCity]).at(cities[j]) < minDistance) {
                minDistance = adjMatrix.at(cities[currentCity]).at(cities[j]);
                nearestCity = j;
            }
        }

        // Atualiza o custo e marca a cidade como visitada
        totalCost += minDistance;
        visited[nearestCity] = true;
        route.push_back(cities[nearestCity]);
        currentCity = nearestCity;
    }

    // Retorna ao ponto de origem (primeira cidade)
    totalCost += adjMatrix.at(cities[currentCity]).at(cities[0]);

    return {totalCost, route};
}
